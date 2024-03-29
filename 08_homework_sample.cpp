﻿// chapter7.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include <iostream>
using namespace std;

class vehicle {
	int num_wheels;
	int range;
public:
	vehicle(int w, int r) {
		num_wheels = w;
		range = r;
	}
	void showv() {
		cout << "num wheels is: " << num_wheels << endl;
		cout << "range is: " << range << endl;
	}
};

// car と truckの継承の時、virtualの宣言が必要
// これを外すと、vanを作るときに、vehicleが2度呼ばれることになりエラーになる。
class car : virtual public vehicle { //*** virtual
	int passengers;
public:
	car(int w, int r, int p): vehicle(w,r){
		passengers = p;
	}
	void show() {
		cout << "\n car" << endl;
		showv();
		cout << "This is CAR: maximum passengers is " << passengers << endl;
	}
};

class truck : virtual public vehicle { //*** virtual
	int loadlimit;
public:
	truck(int w, int r, int l) : vehicle(w, r) {
		loadlimit = l;
	}
	void show() {
		cout << "\n truck" << endl;
		showv();
		cout << "This is TRUCK: loadlimit is " << loadlimit << endl;
	}
};


// ******* homework ******

// vanはcarとtruckの両方から継承する
// car, truckはそれぞれvehicleから継承するため、それらの定義にvirtualが必要
class van : public car, public truck {
	bool fourth_seat; //4列目座席
public:
	/*
	van(int w, int r, int p, int l, bool f) : car(w, r, p), truck(w, r, l){
		fourth_seat = f; 
	}
	*/
	van(int w, int r, int p, int l, bool f) : vehicle(w, r), car(w, r, p), truck(w, r, l){
		fourth_seat = f;
	}

	void show() {
		cout << "\n van" << endl;
		car::show();
		truck::show();
		cout << "This is VAN: availability of fourth_seat is " << fourth_seat << endl;
	}
};

// vanを継承するminivan
// この実装では、minivanは積載量や4列目シートは考えない。　
// virtual を使って vehicle が間接的に複数回呼ばれるのを防いでいる。
// コンストラクタは、通常直近の親コンストラクタのみ呼べばいいのだが、
// virtualをつかっている今回の場合、明示的にvehicleのコンストラクタを呼ぶ必要がある。
class minivan : public van {
	bool slidedoor; // スライドドア
public:
	//このコンストラクタで、vehicle(w,r)を明示的に呼ぶ必要がある。
	minivan(int w, int r, int p,  bool s) : vehicle(w,r), van(w, r, p, 0, false){
		slidedoor = s;
	}
	void show() {
		cout << "\n minivan" << endl;
		van::show();
		cout << "This is MINIVAN: availability of slide door is " << slidedoor << endl<<endl;
	}
};


int main()
{
	car c(5, 500, 4);
	c.show();

	truck t(4, 1000, 30000);
	t.show();
	
	// homework

	van v(4, 500, 15, 1200, true);
	v.show();

	minivan m(4, 500, 4, true);
	m.show();


    return 0;
}

