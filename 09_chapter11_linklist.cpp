#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define MAX_MEMBER 10

/* 汎用的なリンクリスト*/
/* data_t は任意の型。（以下のmember型などを使う）*/
template <class data_t> class list {
	//list生成時、ここでdata_t型のdefault constructorが呼ばれる。(要準備）
	data_t data;
	list *next;
public:
	//コンストラクタ：引数のdata_t型のdataは参照渡し
	list(const data_t &d) { data = d; next = 0; } 
	void add(list *node) { node->next = this; next = 0; }
	list *getnext() { return next; }
	data_t &getdata() { return data; } //参照返し
};


//リストで連結する予定のmemberクラス
class member {
public:
	int id;
	string name;
	member(int x, string n) {
		id = x;
		name = n;
		cerr << "constructor" << endl;
	}
	member() {
		id = -1;
		name = "Not available";
		cerr << "default constructor" << endl;
	}
	member(const member &m) {
		id = m.id;
		name = m.name;
		cerr << "copy constructor " << endl;
	}
};


int main()
{
	int num_member = 0;
	member *m[MAX_MEMBER];//memberクラスのインスタンスを指すためのポインタ配列
	ostringstream oss; //文字列を連結して扱える便利なクラス

	//登録する名前を準備（普通は外部から読み取ったりする。）
	string namelist[MAX_MEMBER];
	do {
		cerr << "How many members? max= " << MAX_MEMBER << endl;
		cin >> num_member;
	} while (num_member > MAX_MEMBER);

	cerr << "number of members is " << num_member << endl;
	cerr << "-----------------\n";

	//num_member人分のインスタンスを準備
	for (int i = 0; i < num_member; i++) {
		//便利にstringのインスタンスに値を格納するための方法
		//namelist[i]に、名前（適当）を格納。
		oss.str("");
		oss.clear();
		oss << " tempolary name [ " << i <<" ]";
		namelist[i] = oss.str();
		cerr << namelist[i]<<endl;

		//memberクラスのインスタンス生成（コンストラクタ呼び出し）
		m[i] = new member(i, namelist[i]);
	}

	cerr << "***** member information ready ***** \n\n";

	//最初のmemberとしてm[0]の中身を登録
	list<member> start(*m[0]); //***（注1）***
	
	/* ***（注1）***
		start=*m[0]とも書ける。list型であるstartに、初期値として*m[0]を渡している。
		つまり、listのコンストラクタに、*m[0]を渡している。　代入でないことに注意。

		listのコンストラクタでは　data_t data と引数なしでオブジェクトが宣言されているので、
		新しい要素を追加する際に、data_t型、つまりmemberクラスにのdefaultコンストラクタが呼ばれる。
		listのコンストラクタが参照渡しでなければ、memberのコピーコンストラクタが呼ばれる
	*/
	
	
	list<member> *p; //Listの現在見ているオブジェクトへのポインタ
	list<member> *last;//Listの最後のオブジェクトへのポインタ
	//現時点でのstartノード(m[0])がlastノード
	last = &start;

	cerr << "\n ***** add members to the link ***** \n";

	for(int i = 0; i < num_member; i++) {
		cerr << "[  " << i <<" ] list add start \n";
		p = new list<member>(*(m[i]));//***（注2）***
		cerr << "[  " << i <<" ] list add end \n";
		
		p->add(last); // p->add(last)とも書ける。
		last = p;
	}
	/* ***（注2）***
	pの先に、member型の*m[i]を初期値としてlistクラスのインスタンスを生成している。
	注1と同様、memberのデフォルトコンストラクタが呼ばれる。
	listのコンストラクタが参照渡しでなければ、コピーコンストラクタも呼ばれる。
	*/

	//リストの追跡（確認）
	// list::getdata()が参照返しでない場合、p->getdata()でcopy constructorが呼ばれる。
	cerr << "\n\n ***** display list *****\n\n";
	p = &start;
	cerr << "- 0 - \n";
	while (p) {
		cerr << "- A - \n";
		cerr << "id= "<< p->getdata().id<<endl;
		cerr << "- B - \n";
		cerr << "name= "<< p->getdata().name<<endl;
		cerr << "- C - \n";
		p = p->getnext();
		cerr << "- D - \n";
	}
	cerr << endl;

    return 0;
}

