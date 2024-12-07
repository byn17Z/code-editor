#include "rawprocessing.h"
#include "APIOFLexical_debugver.h"
#include <vector>
#include <stack>
#include <unordered_set>
#include <algorithm>

const unordered_set<string> typeword = { "void", "int", "char", "float", "double", "bool", "string", "long", "short", "signed", "unsigned" };

//�ҵ����������ֹλ��
int pairing(vector<pair<string, string> > tokens, int start,int n) {
	int line = -1;
	stack<string> s;
	int i = start;
	//���������for() balabala;
	//��for()
	//		balabala;
	//���ֲ��������ŵ�������
	while (tokens[i].second != "{") {
		if (i < n - 1 && tokens[i].first == "startofline" && tokens[i + 1].second != "{") {
			if (tokens[i - 1].second != ";") { //������һ�е��к�
				return stoi(tokens[i].second);
			}
			else //�򷵻ر��е��к�
				return stoi(tokens[i].second) - 1;
		}
		i++;
	}
	for (i = start; i < n; i++) {
		if (tokens[i].second == "{") {
			s.push("1");
		}
		if (tokens[i].second == "}") {
			s.pop();
			if (s.empty()) {
				for(int j=i-1;j>=0;j--){
					if(tokens[j].first == "startofline"){
						line = stoi(tokens[j].second);
						break;
					}
				}
				return line;
			}
		}
	}
	return line;
}

//�ҵ����еĺ�������
unordered_set<string> findfuns(vector<pair<string, string> > tokens,int n) {
	unordered_set<string> functionnames;
	for (int i = 0; i < n; i++) {
		if (tokens[i].first == "KeyWord" && typeword.contains(tokens[i].second)) {
			if (i<n-2&&(tokens[i + 1].first == "IDEN"||tokens[i+1].second=="main") && tokens[i + 2].second == "(") {
				functionnames.insert(tokens[i + 1].second);
			}
		}
		if(tokens[i].second== "{"){
			int end = pairing(tokens, i,n);
			for (;i<n; i++) {
				if (tokens[i].first == "startofline" && tokens[i].second == to_string(end)) {
					while (tokens[++i].second != "}");
					break;
				}
			}
		}
	}
	return functionnames;
}

unordered_set<string> findstructs(vector<pair<string, string> > tokens, int n) {
	unordered_set<string> structnames;
	for (int i = 0; i < n; i++) {
		if (tokens[i].second == "struct" ) {
			structnames.insert(tokens[i + 1].second);
		}
		if (tokens[i].second == "{") {
			int end = pairing(tokens, i, n);
			for (; i < n; i++) {
				if (tokens[i].first == "startofline" && tokens[i].second == to_string(end)) {
					while (tokens[++i].second != "}");
					break;
				}
			}
		}
	}
	return structnames;
}

//�ҵ����е�������
vector<pair<string, int> > findallscope(vector<pair<string, string> > tokens, unordered_set<string> functionname, unordered_set<string> structname, int n) {
	int currentline = 0;
	vector<pair<string, int> > result;

	for (int i = 0; i < n-2; i++) {
		if (tokens[i].first == "startofline") {
			currentline = stoi(tokens[i].second);
		}

		if (tokens[i].first == "KeyWord") {
			if(tokens[i].second == "for") {
				result.push_back(make_pair("startfor", currentline));
				result.push_back(make_pair("endfor", pairing(tokens,i,n)));
			}
			if(tokens[i].second == "while"){
				result.push_back(make_pair("startwhile", currentline));
				result.push_back(make_pair("endwhile", pairing(tokens,i,n)));
			}
			if(tokens[i].second == "if"){
				result.push_back(make_pair("startif", currentline));
				result.push_back(make_pair("endif", pairing(tokens,i,n)));
			}
			if(tokens[i].second == "else"){
				result.push_back(make_pair("startelse", currentline));
				result.push_back(make_pair("endelse", pairing(tokens,i,n)));
			}
			if(i<n-1&&functionname.contains(tokens[i+1].second)){
				result.push_back(make_pair("startfun", currentline));
				result.push_back(make_pair("endfun", pairing(tokens,i,n)));
			}
			if (i < n - 1 && structname.contains(tokens[i + 1].second)) {
				result.push_back(make_pair("startstruct", currentline));
				result.push_back(make_pair("endstruct", pairing(tokens, i, n)));
			}
		}
	}
	return result;
}

//���������к����� 
vector<pair<string, int> > findALLscope(string filename) {
	vector<pair<string, string> > tokens = DB::gettoken(filename);
	int n = tokens.size();
	unordered_set<string> functionname = findfuns(tokens,n);
	unordered_set<string> structname = findstructs(tokens, n);

	vector<pair<string, int> > scopes = findallscope(tokens,functionname,structname,n);
	stable_sort(scopes.begin(), scopes.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
		return a.second < b.second;
		});
	return scopes;
}