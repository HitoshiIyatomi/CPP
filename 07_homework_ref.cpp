
#include <iostream>
using namespace std;

class coord {
	int x, y;
public:
	int *p;
	int len;
	//コンストラクタ
	//　（このコンストラクタはデフォルトコンストラクタとしても動作）
	coord(int l = 5, int i = 0, int j = 0) {
		x = i;
		y = j;
		len = l;
		p = new int[len];
		for (int k = 0; k < len; k++)
			p[k] = k;
		cerr << "constructor" << endl;
	}

	//デストラクタ
	~coord() {
		delete[] p;
	}

	//コピーコンストラクタ
	//これがあるときとない時の比較をレポートで検証しましょう。
	//どのタイミングでコピーコンストラクタが呼ばれるかをしっておくことがとても大切です。
	//コピーコンストラクタがない場合、heap領域にメモリを確保したオブジェクト（今回など）を
	// 関数に値渡し、値戻しを行うとプログラムが動作しない。（下の(1)の=演算子利用時）
	coord(const coord &ob) {
		x = ob.x;
		y = ob.y;
		len = ob.len;
		p = new int[len];
		for (int k = 0; k < len; k++)//とても遅い実装だがわかりやすさ優先
			p[k] = ob.p[k];//この左辺は新しく作られる側
		cerr << "copy constructor" << endl;
	}

	/*
	//　代入演算子の定義
	//　ここで(1)値渡し、値戻しの場合と
	// 　　　 (2)参照渡し、参照戻しの場合　で動作を比較できると良い。
	//  これを変えたときに、コピーコンストラクタの呼ばれ方の違いを検討できるといい。
	//  (2)参照渡しの場合、コピーコンストラクタは呼ばれない
	//  コピーコンストラクタがない状態で、(1)値渡しの=を使うとエラーになる。
	*/
	coord operator=(const coord ob);    // (1) 代入演算子の定義。（値渡し）
	//coord &operator=(const coord &ob);// (2) 代入演算子の定義。（参照渡し）

	//　ここから下は自分でしっかり定義する。

	//2項演算子
	coord operator+(coord &ob);
	coord operator-(coord &ob);//2項演算子としての- （引き算）
	

	//単項演算子
	coord operator++();
	coord operator++(int notused);
	coord operator-();//単項演算子としての- （－）

	//　[]演算子
	int &operator[](int i) { return p[i]; }

	void show(int i);
};


//　＝演算子を値渡しにする場合
//　コピーコンストラクタがないと動作しない。（エラーになる）
coord coord::operator=(const coord ob)
{
	x = ob.x;
	y = ob.y;
	cout << "=（代入　値渡し）" << endl;
	return *this;
}

/*　
// ＝演算子を参照渡し、戻しにする場合
// コピーコンストラクタがなくても動作する。
coord &coord::operator=(const coord &ob)
{
x = ob.x;
y = ob.y;
cout << "=（代入 参照渡し参照返し）" << endl;
return *this;
}
*/

coord coord::operator+(coord &ob)
{
	coord temp;
	temp.x = x + ob.x;
	temp.y = y + ob.y;
	cerr << "+（足し算）" << endl;
	return temp;
}

coord coord::operator-(coord &ob)
{
	coord temp;
	temp.x = x - ob.x;
	temp.y = y - ob.y;
	cerr << "-（引き算）" << endl;
	return temp;
}

coord coord::operator-()
{
	x = -x;
	y = -y;
	cerr << "-（マイナス）" << endl;
	return *this;
}


coord coord::operator++()
{
	x++;
	y++;
	cerr << "++（前置）" << endl;
	return *this;
}

coord coord::operator++(int notused)
{
	x += 2;
	y += 2;
	cerr << "++（後置）" << endl;
	return *this;
}


void coord::show(int i)
{
	cerr << "[show " << i << " ] :  " << x << "," << y << endl;
}




int main()
{
	coord ob1(10, 2, 3), ob2, ob3;

	//単項演算子の確認（前置型）
	ob1.show(1);
	++ob1;
	ob1.show(1);
	cout << endl;

	//単項演算子の確認（後置型）
	ob2.show(2);
	ob2++;
	ob2.show(2);
	cout << endl;

	//今回の実装では、コピーコンストラクタがあるので
	//*thisを返す関数は、コピーコンストラクタが呼ばれることを確認
	//コピーコンストラクタがない場合、関数からの戻りが値渡しになるので注意
	//（heapにメモリ領域を確保しているクラスにこの関数をそのまま適用する場合、
	// 関数を抜けるときに*thisが参照しているheapの領域が
	//　デストラクタで破壊されるので、エラーになる）

	//代入演算子の例
	//　代入は、初期化ではないのでコピーコンストラクタは呼ばれないことを確認
	ob3.show(3);
	ob3 = ob1;
	ob3.show(3);
	cout << endl;

	//2項演算子と=を用いた代入の例
	//　2項演算子(+)では、tempを返している。ここでもコピーコンストラクタが呼ばれる。
	ob3.show(31);
	ob3 = (ob1 + ob2);
	ob3.show(31);
	cout << endl;


	//初期化の例。コピーコンストラクタが呼ばれob1の値でob4が初期化され作られる
	//コピーコンストラクタはob4生成の際に、1回呼ばれる。
	coord ob4 = ob1;
	ob4.show(4);
	ob1.show(41);
	cout << endl;

	//ob1-ob2の引き算でコピーコンストラクタが呼ばれ、そのままそのコピーがob4の初期値として使われる。
	//2回呼ばれそうだが、コンパイラが工夫して（ob1-ob2がコピーであることがわかっているため、再度コピーが作られず）
	//コピーコンストラクタが呼ばれるのは1回にまとめられる
	ob1.show(51);
	ob2.show(52);
	coord ob5 = ob1 - ob2;
	ob5.show(5);
	cout << endl;

	// []演算子の動作確認
	cout << "[]演算子の動作確認" << endl;
	for(int i=0; i<ob1.len; i++)
		cout << ob1[i] << endl;

	return 0;
}
/* point 
・コピーコンストラクタは、初期化の時のみ呼ばれ、代入の時には呼ばれない
・参照渡し、参照返しの関数((2)の＝など)の場合、コピーコンストラクタは呼ばれない
・コピーコンストラクタがない状態で、値渡しの関数((1)の＝など)が呼ばれると、今回のようにheap領域にメモリを確保しているオブジェクト
　は、一方のオブジェクト破棄の際に、共有のメモリが破壊されてしまうためエラーになる。（のでだめ）
・(1)の＝の実装をしていても、コピーコンストラクタがあれば、値渡しは行われないので、大丈夫。ただしコピーをするため遅い。
・[]演算子は、オブジェクト内の配列を便利に使える。
*/
