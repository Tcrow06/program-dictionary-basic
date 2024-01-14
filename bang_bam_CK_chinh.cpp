#include<bits/stdc++.h>
#include <conio.h>
using namespace std;
#define SIZE 4000
#define MAX_LET 28 
#define sug 7
struct Word{
	string word;
	string mean;
};
struct  Node{
	Word Info;
	Node* pNext;
};
struct Dic{
	Node*pHead;
	Node*pTail;
	ktao(){
		pHead= NULL;
		pTail = NULL;
	}
};
//tao node cay tien to
struct LNode{
	char info;
	LNode* child[MAX_LET];
	bool isEnd;
	LNnode(){
		for(int i=0; i<MAX_LET; ++i)
			child[i]=NULL;
		isEnd=0;
	}
};
LNode * root = new LNode();

void AddLet(string&s){
	LNode* u = root;
	for(int i =0; i< s.size(); ++i){
		
		int k ;
		if(s[i]==' '){
			k=26;
		} 
		else if(s[i]=='-'){
			k=27;
		}
		else
	 		k= s[i]-'a';
		if(u->child[k]==NULL) {
			u->child[k]= new LNode();
			u->child[k]->info=s[i];
		}
		u = u->child[k];
	}
	u->isEnd =1;
}
void SugesWord(LNode* root, string&w,int&key){
	if(key<=0||root==NULL)
		return;
	for(int i =0; i<MAX_LET; ++i){
		if(root->child[i]){
			w+= root->child[i]->info;
			if(root->child[i]->isEnd==1){
				cout<<w<<endl;
				key--;
			}
			SugesWord(root->child[i],w,key);
			w.erase(w.begin()+w.size()-1);
		}
		if(key<=0)
			return;
	}
}
LNode* FindFirst(LNode* r, string let){
	if(let.size()==0||r==NULL) return r;
	char x = let[0];
	let.erase(0,1);
	int k;
	if(x==' ') k=26;
	else if(x=='-') k= 27;
	else k= x-'a';
	LNode* pNext = r ->child[k];
	return FindFirst(pNext,let);
}
void chuanHoaThuong(string&s){
	for(int i=0; i<s.size(); i++){
		s[i]=tolower(s[i]);
	}
}
void SugesWord(string s){
	chuanHoaThuong(s);
	LNode* r =FindFirst(root,s);
	if(r==NULL)
		return;
	if(r->isEnd) cout<<s<<endl;
	int key = sug;
	SugesWord(r,s,key);
}
void init(Dic dics[]){
	for(int i =0; i<SIZE;i++){
		dics[i].pHead=NULL;
		dics[i].pTail = NULL;
	}	
}
void chuanHoaThuongVaKhoangTrang(string&x){
	while(x[0]==' ')
		x.erase(x.begin()+ 0);
	while(x[x.size()-1]==' ')
		x.erase(x.begin()+ x.size()-1);
	for(int i= 0 ;i< x.size(); i++){
		if(x[i]==' '&&x[i+1]==' '){
			x.erase(x.begin()+ i);
			i--;
		}
		x[i]= tolower(x[i]);
	}				
}
void xoaKhoangTrangGiua(string&x){
	for(int i=0; i<x.size(); i++)
		if(x[i]==' '){
			x.erase(x.begin()+ i);
			i--;
		}	
}
int hashFunction(string s){
	int hash=0;
	for(int i=0; i<s.size(); i++)
		hash+=(tolower(s[i])-'0')*(i+1);
	return hash%SIZE;
}
Node* CreateNode(Word x){
	
	Node* tmp = new Node();
	tmp -> Info = x;
	tmp -> pNext = NULL;
	return tmp;	
}

bool Find(Dic dic, Word x,Word&y){
	Node* tmp = dic.pHead;
	while(tmp!=NULL){
		string a = tmp->Info.word;
		string b = x.word;
		chuanHoaThuongVaKhoangTrang(a);
		chuanHoaThuongVaKhoangTrang(b);
		if(a==b){
			y=tmp->Info;
			return true;
		}
		tmp=tmp->pNext;	
	}
	return false;
}
void addWord(Dic dics[],Word x){
	int hash = hashFunction(x.word);
	Node* tmp = CreateNode(x);
	if(dics[hash].pHead == NULL){
		dics[hash].pHead = tmp;
		dics[hash].pTail = dics[hash].pHead; 	
	}
	else{
		Word y;
		bool check = Find(dics[hash],x,y);
		if(!check){
			dics[hash].pTail -> pNext = tmp;
			dics[hash].pTail = tmp;
		}
		else return;
	}
}

void printMisWord(Word x){
	cout<<x.mean<<endl;
	cout<<endl;
}
bool ktraChuoiChuCaiLet(string s){
	chuanHoaThuong(s);
	int count =0;
	for(int i=0; i<s.size(); i++){
		if(s[i]>='a'&&s[i]<='z')
			count++;
	}
	if(count==0) return false;
	for(int i=0; i<s.size(); i++)
		if((s[i]<'a'||s[i]>'z')&&(s[i]!=' '&&s[i]!='-'))
			return false;
	return true;
} 
void  DocFile1(Dic dics[]){
	ifstream in("dictionary.txt");
	if(!in) return;
	Word x;
	x.word="@";
	string s;
	string tmp;
	x.mean="";
	while(getline(in,s)){
		if(s[0]=='@'){
			if(x.word!="@"){
				addWord(dics,x);
				x.mean="";
			}
			s.erase(0,1);
			stringstream ss(s);
			getline(ss,x.word,'/');
			chuanHoaThuongVaKhoangTrang(x.word);
			if(ktraChuoiChuCaiLet(x.word))
				AddLet(x.word);
		}
		else {
			if(x.mean.size()>0&&s.size()>2)
				x.mean+="\n";
			x.mean+=s;
		}
	}
	addWord(dics,x);
	in.close(); 
}
void GhiFile(Word x){
	ofstream o;
	o.open("dictionary.txt",ios::app);
	if(!o) return;
	o<<"@"<<x.word<<endl;
	o<<x.mean;
}
void XoaTuFile(string a){
	ifstream in("dictionary.txt");
	ofstream o("temp.txt");
	if(!in) return;
	Word x;
	x.word="@";
	string s;
	string tmp;
	x.mean="";
	string tu;
	while(getline(in,s)){
		if(s[0]=='@'){
			if(x.word!="@"){
				chuanHoaThuongVaKhoangTrang(tu);
				chuanHoaThuongVaKhoangTrang(a);
				if(tu!=a){
					o<<x.word<<endl;
					o<<x.mean<<endl;
				}	
				x.mean="";
			}
			x.word = s;
			stringstream ss(s);
			getline(ss,tu,'/');
			tu.erase(0,1);
		}
		else {
			if(x.mean.size()>0&&s.size()>2)
				x.mean+="\n";
			x.mean+=s;
		}
	}
	in.close(); 
	o.close();
	
	ifstream in1("temp.txt");
	ofstream o1("dictionary.txt");
	if(!in1) return;
	x.word="@";
	x.mean="";
	while(getline(in1,s)){
		if(s[0]=='@'){
			if(x.word!="@"){
				o1<<x.word<<endl;
				o1<<x.mean<<endl;	
				x.mean="";
			}
			x.word = s;
			stringstream ss(s);
			getline(ss,tu,'/');
			tu.erase(0,1);
		}
		else {
			if(x.mean.size()>0&&s.size()>2)
				x.mean+="\n";
			x.mean+=s;
		}
	}
	in1.close(); 
	o1.close();
	remove("temp.txt");
}
string LayTu(string x){
	string s="";
	for(int i =0; i<x.size(); i++){
		if((x[i]>='a'&&x[i]<='z')||x[i]==' '||x[i]=='-')
			s+=x[i];
	}
	return s;
}
void qhd(string a,string b,int&key,int&k)
{
	int n=min(a.size(),b.size());
	string F[n+1][n+1];
	for(int i=0;i<=n;i++)
	{
		F[0][i]="";
		F[i][0]="";
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i-1]==b[j-1])
				F[i][j]=F[i-1][j-1]+a[i-1];
			else
				F[i][j]=(F[i][j-1].size()>F[i-1][j].size())?F[i][j-1]:F[i-1][j];
		}
	}
	if(abs(a.size()-F[n][n].size())<=1&&abs(a.size()-b.size())<=1){
		if(key){
			cout<<"-Goi y:\n";
			key--;
		}
		k--;
		cout<<a<<endl;
	}
		
}
void SugestL1(Dic dic,string x,int&key,int&k){
	while(dic.pHead !=NULL){
		qhd(dic.pHead->Info.word,x,key,k);
		dic.pHead = dic.pHead ->pNext;
		if(k<=0)
			return;
	}
}
void SugestL(Dic dics[],string x){
	int key = 1;
	int k = sug;
	for(int i=0 ; i<SIZE; i++){
		if(dics[i].pHead!=NULL){
			SugestL1(dics[i],x,key,k);
			if(k<=0)
			return;
		}
	}
}
void SearchDic(Dic dics[]){
	string x;
	char c = 14;
	do{
		system("cls");
		cout<<"Nhap tu can tra: "<<x<<"_"<<endl;
		if(x.size()&&ktraChuoiChuCaiLet(x)) SugesWord(x);
		c = _getch();
		
		if(c == 8){  //back
			if(x.size()==0) continue;
			x.erase(x.begin()+x.size()-1);
		}
		else{
			x+=c;
		}
	}while(c !=13);
	system("cls");
	cout<<"Nhap tu can tra: "<<x<<endl;
	chuanHoaThuongVaKhoangTrang(x);
	Word w;
	w.word = LayTu(x);bool check=false; 
	int i = hashFunction(w.word); 
	if(dics[i].pHead!=NULL)
		if(Find(dics[i],w,w)){
			check = true;
		}	
	if(check){
		cout<<"-Ket qua: \n";
		printMisWord(w);
	}
	else{
		cout<<"-Khong co trong tu dien\n";
		SugestL(dics,x);
	}
	
}
bool kiemTraChuoiChuCaiVaSo(string s){
	for(int i=0; i<s.size(); i++){
		if((s[i]<'a'||s[i]>'z')&&(s[i]<'1'||s[i]>'9')&&s[i]!=' ')
			return false;
	}
	return true;
}
void chuanHoaChuoiSo(string&s){
	chuanHoaThuongVaKhoangTrang(s);
	if(s.size()>=3)
		xoaKhoangTrangGiua(s);
}
void InsertHash(Dic dics[]){
	string s;
	Word x;
	cout<<"-Nhap tu tieng anh: ";
	do{
		getline(cin,s);
		if(ktraChuoiChuCaiLet(s)&&s.size()>0){
			chuanHoaThuongVaKhoangTrang(s);
			Word tmp;
			tmp.word =s;
			int hash=hashFunction(s);
			if(Find(dics[hash],tmp,tmp)){
				cout<<"-Tu tieng anh da ton tai trong tu dien:\n";
				return;
			}
			else break;	
		}
		else cout<<"-Khong hop le.Nhap lai tu tieng anh: ";
	}while(true);
	chuanHoaThuongVaKhoangTrang(s);
	x.word = s;
	AddLet(s);
	x.mean="";
	do{
		cout<<"-Nhap tu loai: ";
		do{
			getline(cin,s);
			if(ktraChuoiChuCaiLet(s)&&s.size()>0)
				break;
			cout<<"-Khong hop le.Nhap lai tu loai: ";
		}while(true);
		x.mean+="*"+s+"\n";
		cout<<"-Nhap nghia tieng viet: ";
		do{
			getline(cin,s);
			if(s.size()>0) break;
			cout<<"-Khong hop le. Nhap lai nghia tieng viet: ";
		}while(true);
		x.mean+="-"+s +"\n";
		
		cout<<"Nhap vi du: ";getline(cin,s);
		if(s.size()>0)
			x.mean+="=" + s+"\n";
		cout<<"Ban co muon nhap them tu loai va nghia khong\n"; 
		cout<<"1. Co\n";
		cout<<"0. Khong\n";
		cout<<"-Nhap lua chon: ";
		string choice;
		getline(cin,choice);
		chuanHoaChuoiSo(choice);
		while(choice[0]<'0'||choice[0]>'1'||choice.size()>1){
			cout<<"Nhap lai lua chon: ";
			getline(cin,choice);
			chuanHoaChuoiSo(choice);
		}
		if(stoi(choice)==0)
			break;
		
	} while(true);
	addWord(dics,x);
	GhiFile(x);
	cout<<"-Them thanh cong\n";
	
}
bool RemoveNode(Dic&r, string s){
	Node* truoc= r.pHead;
	Node* sau=NULL;
	while(truoc!=NULL){
		if(truoc->Info.word==s)
			break;
		sau= truoc;
		truoc = truoc->pNext;
	}
	if(truoc==NULL)
		return false;
		
	if(sau==NULL){
		r.pHead = r.pHead ->pNext;
		return true;
	}
	sau->pNext= truoc->pNext;
	delete truoc;
	return true;
}
void RemoveLet(string s){
	chuanHoaThuongVaKhoangTrang(s);
	LNode* r = root;
	for(int i=0; i<s.size(); i++){
		r = r->child[s[i]-'a'];
	}
	r->isEnd=0;	
}
void RemoveHash(Dic dics[]){
	string s;
	Word x;
	cout<<"-Nhap tu tieng anh: ";
	do{
		getline(cin,s);
		chuanHoaThuongVaKhoangTrang(s);
		if(ktraChuoiChuCaiLet(s)){
			Word tmp;
			tmp.word =s;
			int hash=hashFunction(s);
			if(!RemoveNode(dics[hash],s)){
				cout<<"-Tu tieng anh khong ton tai trong tu dien:\n";
				return;
			}
			else{
				cout<<"Xoa thanh cong\n";
				XoaTuFile(s);
				RemoveLet(s);
				return;
			}
		}
		else cout<<"-Khong hop le.Nhap lai tu tieng anh: ";
	}while(true);
}

int menu(){
	cout<<"1. Tra cuu tu\n";
	cout<<"2. Them tu vao danh sach tu dien\n";
	cout<<"3. Xoa tu khoi danh sach tu dien\n";
	cout<<"0. Thoat\n";
	cout<<"-Lua chon cua ban la: ";
	string choice;
	getline(cin,choice);
	chuanHoaChuoiSo(choice);
	while(choice[0]<'0'||choice[0]>'3'||choice.size()>1){
		cout<<"Nhap lai lua chon: ";
		getline(cin,choice);
		chuanHoaChuoiSo(choice);
	}
	return stoi(choice);
}
void OSearchDic(Dic dics[]){
	do{
		system("cls");
		SearchDic(dics);
		cout<<"\n1. Tiep tuc tra\n";
		cout<<"2. Tro ve lua chon ban dau\n";
		cout<<"0. Thoat chuong trinh\n";
		cout<<"-Lua chon cua ban la: ";
		string choice;
		getline(cin,choice);
		chuanHoaChuoiSo(choice);
		while(choice[0]<'0'||choice[0]>'2'||choice.size()>1){
			cout<<"Nhap lai lua chon: ";
			getline(cin,choice);
			chuanHoaChuoiSo(choice);
		}
		int c=stoi(choice);
		if(c==1)
			continue;
		else if(c ==0) exit(0);
		else return;
	}while(true);
}
void OInsertDic(Dic dics[]){
	do{
		system("cls");
		InsertHash(dics);
		cout<<"\n1. Tiep tuc them tu\n";
		cout<<"2. Tro ve lua chon ban dau\n";
		cout<<"0. Thoat chuong trinh\n";
		cout<<"-Lua chon cua ban la: ";
		string choice;
		getline(cin,choice);
		chuanHoaChuoiSo(choice);
		while(choice[0]<'0'||choice[0]>'2'||choice.size()>1){
			cout<<"Nhap lai lua chon: ";
			getline(cin,choice);
			chuanHoaChuoiSo(choice);
		}
		int c=stoi(choice);
		if(c==1)
			continue;
		else if(c ==0) exit(0);
		else return;	
	}while(true);
}
void ORemoveDic(Dic dics[]){
	do{
		system("cls");
		RemoveHash(dics);
		cout<<"\n1. Tiep tuc xoa tu\n";
		cout<<"2. Tro ve lua chon ban dau\n";
		cout<<"0. Thoat chuong trinh\n";
		cout<<"-Lua chon cua ban la: ";
		string choice;
		getline(cin,choice);
		chuanHoaChuoiSo(choice);
		while(choice[0]<'0'||choice[0]>'2'||choice.size()>1){
			cout<<"Nhap lai lua chon: ";
			getline(cin,choice);
			chuanHoaChuoiSo(choice);
		}
		int c=stoi(choice);
		if(c==1)
			continue;
		else if(c ==0) exit(0);
		else return;	
	}while(true);
}
void option(Dic dics[]){
	do{
		system("cls");
		int choice = menu();
		if(choice ==0) exit(0);
		if(choice==1){
			OSearchDic(dics);
		}
		else if(choice ==2){
			OInsertDic(dics);
		}
		else if(choice ==3){
			ORemoveDic(dics);
		} 
	}while(true);
}
int main(){
	Dic dics [SIZE];
	init(dics);
	DocFile1(dics);
	option(dics);
	return 0;
} 





