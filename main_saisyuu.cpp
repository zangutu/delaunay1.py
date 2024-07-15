//jimenn.cpp
#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cmath>
#include <stack>
#define kesson -9999.99
#define tansaku 0.11//深さ優先探索の終了条件
using namespace std;
struct Point{
    double x;
    double y;
    double z;
};

bool hantei(vector<vector<double>>& vz,vector<vector<int>>& used,int j,int i,int tmp){
    int dx[] = { 0,  1, 1, 1, 0, -1, -1, -1};
    int dy[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    int nx, ny;
    bool flag=true;
    for(int k=0;k<8;k++){
            nx=dx[k]+j;
            ny=dy[k]+i;
            if(tmp>vz[nx][ny]||vz[nx][ny]>tmp+1){
                flag = false;
            }
}
return flag;
}

vector<int> mode(vector<vector<double>>& vz, vector<vector<int>>& check,double min,double max,int xd,int yd){//1mの階級幅でz座標を分割して、階級値を添え字として値の個数が入った配列を返す関数
    min = int(min);
    max = int(max);
    vector<int> ans(max-min+1);
    for(int i = 0; i < yd + 1; i++){
        for(int j = 0; j < xd + 1; j++){
            if(check[j][i]==1){
                ans[int(vz[j][i])-min]++;
            }
        }
    }
    return ans;
}
double rinsetu_min(vector<vector<double>>& vz,vector<vector<int>>& used,int j,int i){
    vector<double> k;
    if(used[j-1][i]==1) k.push_back(vz[j-1][i]);
    if(used[j-1][i+1]==1) k.push_back(vz[j-1][i+1]);
    if(used[j][i+1]==1) k.push_back(vz[j][i+1]);
    if(used[j+1][i+1]==1) k.push_back(vz[j+1][i+1]);
    if(used[j+1][i]==1) k.push_back(vz[j+1][i]);
    if(used[j+1][i-1]==1) k.push_back(vz[j+1][i-1]);
    if(used[j][i-1]==1) k.push_back(vz[j][i-1]);
    if(used[j-1][i-1]==1) k.push_back(vz[j-1][i-1]);
    if(k.size()==0){return kesson;}
    else return double(*min_element(k.begin(),k.end()))-5;//隣接点の地面のz座標の-5の点を返す
}
double find_min(vector<vector<double>>& vz, vector<vector<int>>& check,vector<vector<int>>& used,int xd,int yd){//二重配列の最小値を返す関数
    bool flag=false;
    double min;
    for(int i = 0; i < yd + 1; i++){
        for(int j = 0; j < xd + 1; j++){
            if(check[j][i]==1&&used[j][i]==0&&flag==false){
                min = vz[j][i];
                flag = true;
            }
            if(check[j][i]==1&&used[j][i]==0&&flag==true&&min>vz[j][i]){
                min = vz[j][i];
            }
        }
    }
    return min;
}
double find_max(vector<vector<double>>& vz, vector<vector<int>>& check,vector<vector<int>>& used,int xd,int yd){//二重配列の最大値を返す関数
    bool flag=false;
    double max;
    for(int i = 0; i < yd + 1; i++){
        for(int j = 0; j < xd + 1; j++){
            if(check[j][i]==1&&used[j][i]==0&&flag==false){
                max = vz[j][i];
                flag = true;
            }
            if(check[j][i]==1&&used[j][i]==0&&flag==true&&max<vz[j][i]){
                max = vz[j][i];
            }
        }
    }
    return max;
}


void dfs(const vector<vector<double>>& vz, vector<vector<int>>& used,int w,int h,int x, int y) {//深さ優先探索　再帰を用いるとオーバーフローが起きたので、スタックを用いた
    stack<pair<int, int>> st;
    st.emplace(x, y);
    used[x][y]=1;
    int dx[] = { 0,  1, 1, 1, 0, -1, -1, -1};
    int dy[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    int nx, ny;
    while (!st.empty()) {
        auto [x, y] = st.top();
        st.pop();
        for(int i=0;i<8;i++){
            nx=dx[i]+x;
            ny=dy[i]+y;
            if((nx >= 0 && nx < w) && (ny >= 0 && ny < h)&&used[nx][ny]==0&&vz[nx][ny]-vz[x][y]<=tansaku){
                used[nx][ny]=1;
                st.emplace(nx,ny);
            }
        }
    }
}

void gaisyuu(vector<vector<int>>& used,int w,int h,int j,int i){
    int dx[] = { 0,  1, 1, 1, 0, -1, -1, -1};
    int dy[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    int nx, ny;
    for(int k=0;k<8;k++){
            nx=dx[k]+j;
            ny=dy[k]+i;
            if((nx >= 0 && nx < w) && (ny >= 0 && ny < h)&&used[nx][ny]==1){
                used[j][i]=2;
            }
}
}

void write(const char *Filename){

    //ファイル入力
    ifstream ifs(Filename);
	string str;
    double x_tmp,y_tmp,z_tmp;
    vector<Point> v;
    Point tmp_input;
	while (getline(ifs,str)) {
	    stringstream ss(str);
	    ss >> x_tmp >> y_tmp >> z_tmp;
        tmp_input = {x_tmp,y_tmp,z_tmp};
        v.push_back(tmp_input);
    }
	int n=v.size();
	double xmax=v[0].x,xmin=v[0].x,ymax=v[0].y,ymin=v[0].y;
	for(int i=0;i<n;i++){
		if(xmax<v[i].x) xmax=v[i].x;
		if(xmin>v[i].x) xmin=v[i].x;
		if(ymax<v[i].y) ymax=v[i].y;
		if(ymin>v[i].y) ymin=v[i].y;
	}
	int xd=xmax-xmin;
    int yd = ymax-ymin;
    vector<vector<double>> vz (xd + 1, vector<double>(yd + 1, 0));//x,y,z座標を管理する配列
    vector<vector<int>> check (xd + 1, vector<int>(yd + 1, 0));//vz配列に値を入れたかどうかを判定する配列
    for(int i=0;i<n;i++){
        vz[v[i].x-xmin][v[i].y-ymin]= v[i].z;
        check[v[i].x-xmin][v[i].y-ymin] = 1;
    }

    vector<vector<int>> used(xd+1,vector<int> (yd+1));//建物地面判定用の配列
      //欠損店補完
      int hokan;
    vector<int> flag(9);
for(int i=1;i<yd;i++){
    for(int j=1;j<xd;j++){
        double sum=0;
        if(check[j][i]==0||check[j-1][i]==0||check[j+1][i]==0||check[j][i-1]==0||check[j-1][i-1]==0||check[j+1][i-1]==0||check[j][i+1]==0||check[j-1][i+1]==0||check[j+1][i+1]==0){
            continue;
        }
        if(vz[j][i]==kesson||vz[j-1][i]==kesson||vz[j+1][i]==kesson||vz[j][i-1]==kesson&&vz[j-1][i-1]==kesson||vz[j+1][i-1]==kesson||vz[j][i+1]==kesson||used[j-1][i+1]==kesson||vz[j+1][i+1]==kesson){
            int s=0;
            if(vz[j-1][i]!=kesson) sum+=vz[j-1][i];
            else{
                s++;flag[0]=1;
            }
            if(vz[j-1][i+1]!=kesson) sum+=vz[j-1][i+1];
            else{
                s++;flag[1]=1;
            }
            if(vz[j][i+1]!=kesson) sum+=vz[j][i+1];
            else{
                s++;flag[2]=1;
            }
            if(vz[j+1][i+1]!=kesson) sum+=vz[j+1][i+1];
            else{
                s++;flag[3]=1;
            }
            if(vz[j+1][i]!=kesson) sum+=vz[j+1][i];
            else{
                s++;flag[4]=1;
            }
            if(vz[j+1][i-1]!=kesson) sum+=vz[j+1][i-1];
            else{
                s++;flag[5]=1;
            }
            if(vz[j][i-1]!=kesson) sum+=vz[j][i-1];
            else{
                s++;flag[6]=1;
            }
            if(vz[j-1][i-1]!=kesson) sum+=vz[j-1][i-1];
            else{
                s++;flag[7]=1;
            }
            if(vz[j][i]!=kesson) sum+=vz[j][i];
            else{
                s++;flag[8]=1;
            }
            hokan=sum/(9.0-s);
            if(flag[0]){
                vz[j-1][i]=hokan;
                flag[0]=0;
            }
            if(flag[1]){
                vz[j-1][i+1]=hokan;
                flag[1]=0;
            }
            if(flag[2]){
                vz[j][i+1]=hokan;
                flag[2]=0;
            }
            if(flag[3]){
                vz[j+1][i+1]=hokan;
                flag[3]=0;
            }
            if(flag[4]){
                vz[j+1][i]=hokan;
                flag[4]=0;
            }
            if(flag[5]){
                vz[j+1][i-1]=hokan;
                flag[5]=0;
            }
            if(flag[6]){
                vz[j][i-1]=hokan;
                flag[6]=0;
            }
            if(flag[7]){
                vz[j-1][i-1]=hokan;
                flag[7]=0;
            }
            if(flag[8]){
                vz[j][i]=hokan;
                flag[8]=0;
            }
        }
    }
}

//深さ優先探索    
for(int i=0;i<yd+1;i++){
    for(int j=0;j<xd+1;j++){
        if(check[j][i] == 1){
                used[j][i] = 0;
            }else{
                used[j][i] = -1;
            }
    }
}
double min = find_min(vz,check,used,xd,yd);
double max = find_max(vz,check,used,xd,yd);
vector<int> k=mode(vz,check,min,max,xd,yd);//各階級幅に含まれる個数を要素とする配列

map<double, int,greater<double>> mp;
for(int i=0;i<k.size();i++){
    mp[k[i]]=i;
}
vector<int> index;
double sum=0;
bool flag1=true;
int maxvalue;
for (const auto& p : mp){
    if(sum<=0.3){
    sum += double(p.first/n);
    index.push_back(p.second);
    }
    if(flag1){
        maxvalue=p.second ;
        flag1=false;
    }
}
int maxindex =  *max_element(index.begin(),index.end());
int minindex =  *min_element(index.begin(),index.end());
maxindex += int(min);
maxvalue += int(min);
bool flagindex=true;
if(maxindex-maxvalue>=5){
    flagindex=false;
}

for(int i=1;i<yd;i++){//最頻値がある階級幅内の点を順次深さ優先探索
    //if(flag2)break;
    for(int j=1;j<xd;j++){
        if(flagindex){
            if(used[j][i]==0&&hantei(vz,used,j,i,maxvalue)){
                dfs(vz,used,xd+1,yd+1,j,i);
            }
        }
        else{
            if(used[j][i]==0&&hantei(vz,used,j,i,maxvalue)){
                dfs(vz,used,xd+1,yd+1,j,i);
            }
            if(used[j][i]==0&&hantei(vz,used,j,i,maxindex)){
                dfs(vz,used,xd+1,yd+1,j,i);
            }
        }
    }
}

//データ削減
//used[j][i]=-1は存在しない座標を表す used[j][i]=0は建物判定 used[j][i]=1は地面判定 used[j][i]=2は建物の外周判定
for(int i=1;i<yd;i++){//外れ値の削除
    for(int j=1;j<xd;j++){
        if(vz[j][i]<0){
            check[j][i]=0;
        }
    }
};


for(int i=0;i<yd+1;i++){//建物の外周判定
    for(int j=0;j<xd+1;j++){
        if(i==0){
           gaisyuu(used,xd+1,yd+1,j,i);
        }
        if(j==0){
             gaisyuu(used,xd+1,yd+1,j,i);
        }
        if(i==yd){
           gaisyuu(used,xd+1,yd+1,j,i);
        }
        if(j==xd){
           gaisyuu(used,xd+1,yd+1,j,i);
        }
        if(i!=yd&&i!=0&&i!=yd&&j!=0&&j!=xd&&used[j][i]==0){
           if(used[j-1][i]==1||used[j+1][i]==1||used[j][i-1]==1||used[j-1][i-1]==1||used[j+1][i-1]==1||used[j][i+1]==1||used[j-1][i+1]==1||used[j+1][i+1]==1){
                if(used[j-1][i]+used[j+1][i]+used[j][i-1]+used[j-1][i-1]+used[j+1][i-1]+used[j][i+1]+used[j-1][i+1]+used[j+1][i+1]==8){
                    check[j][i]=0;
            }
                else{
                   used[j][i]=2;
                }
            }
        }
}
}
ofstream outputfile;
std::string filename = "jimentest.txt";
outputfile.open(filename, ios::app);
if(used[xd][yd]!=-1&&check[xd][yd]==0){
    outputfile << xd+xmin << " " << yd+ymin << " " << vz[xd][yd] << " " << 1 << endl;
}
if(used[0][yd]!=-1&&check[0][yd]==0){
    outputfile << xmin << " " << yd+ymin << " " << vz[0][yd] << " " << 1 << endl;
}
if(used[xd][0]!=-1&&check[xd][0]==0){
    outputfile << xd+xmin << " " << ymin << " " << vz[xd][0] << " " << 1 << endl;
}
if(used[0][0]!=-1&&check[0][0]==0){
    outputfile << xmin << " " << yd+ymin<< " " << vz[0][0] << " " << 1 << endl;
}

for(int i=1;i<yd;i++){
    for(int j=1;j<xd;j++){
        if(check[j][i]==0||check[j-1][i]==0||check[j+1][i]==0||check[j][i-1]==0||check[j-1][i-1]==0||check[j+1][i-1]==0||check[j][i+1]==0||check[j-1][i+1]==0||check[j+1][i+1]==0){
            continue;
        }
        if((used[j][i]==0)&&(used[j-1][i]==0)&&(used[j+1][i]==0)&&(used[j][i-1]==0)&&(used[j-1][i-1]==0)&&(used[j+1][i-1]==0)&&(used[j][i+1]==0)&&(used[j-1][i+1]==0)&&(used[j+1][i+1]==0)){//建物データ削除
            vz[j][i] = (vz[j][i]+vz[j-1][i]+vz[j+1][i]+vz[j][i-1]+vz[j-1][i-1]+vz[j+1][i-1]+vz[j][i+1]+vz[j-1][i+1]+vz[j+1][i+1])/9;
            check[j-1][i]=0;check[j+1][i]=0;check[j][i-1]=0;check[j-1][i-1]=0;check[j+1][i-1]=0;check[j][i+1]=0;check[j][i+1]=0;check[j+1][i+1]=0;
        }
        }
}


for(int i=0;i<yd+1;i++){//textファイルに出力（データ削減はまだしていない）
    for(int j=0;j<xd+1;j++){
        if(check[j][i]==1){
        if(used[j][i] == 0){
            outputfile << j+xmin << " " << i+ymin << " " << vz[j][i] << " " << 0 << endl;;
        }
        }
    }
}
//used==2:外周判定されたものの削減
int c;
//vector<vector<int>> delete(xd+1,vector<int> (yd+1));//削除した外周用の配列
for(int i=1;i<yd;i++){
    for(int j=1;j<xd;j++){
        c=0;
        if(used[j][i]==2){
            if(used[j-1][i]==1) c++;
            if(used[j-1][i+1]==1) c++;
            if(used[j][i+1]==1) c++;
            if(used[j+1][i+1]==1) c++;
            if(used[j+1][i]==1) c++;
            if(used[j+1][i-1]==1) c++;
            if(used[j][i-1]==1) c++;
            if(used[j-1][i-1]==1) c++;
            if(c<=2){
                used[j][i]=-1; //外周判定から削除したもの
            }
        }
    }
}

vector<vector<double>> add (xd + 1, vector<double>(yd + 1, kesson));
double add_point;
for(int i=1;i<yd;i++){
    for(int j=1;j<xd;j++){
        if(used[j][i]==2){
           add_point = rinsetu_min(vz,used,j,i);
           if(add_point==kesson){
            continue;
           }
           else{
            add[j][i]=add_point;
           } 
        }
    }
}

//建物と地面の境目の点を追加
for(int i=1;i<yd;i++){
    for(int j=1;j<xd;j++){
        if(check[j][i]==1&&add[j][i]!=kesson){
            outputfile << j+xmin << " " << i+ymin << " " << add[j][i]+5 << " " << 1 << endl;
            if(used[j+1][i]==1){
                outputfile << j+xmin+0.01 << " " << i+ymin << " " << add[j][i] << " " << 0 << endl;
            }
            else if(used[j][i+1]==1){
                outputfile << j+xmin << " " << i+ymin+0.01 << " " << add[j][i] << " " << 0 << endl;
            }
            else if(used[j-1][i]==1){
                outputfile << j+xmin-0.01 << " " << i+ymin << " " << add[j][i] << " " << 0 << endl;
            }
            else if(used[j][i-1]==1){
                outputfile << j+xmin << " " << i+ymin-0.01 << " " << add[j][i] << " " << 0 << endl;
            }
            else if(used[j+1][i+1]==1){
                outputfile << j+xmin+0.01 << " " << i+ymin+0.01 << " " << add[j][i] << " " << 0 << endl;
            }
            else if(used[j+1][i-1]==1){
                outputfile << j+xmin+0.01 << " " << i+ymin-0.01 << " " << add[j][i] << " " << 0 << endl;
            }
            else if(used[j-1][i-1]==1){
                outputfile << j+xmin-0.01 << " " << i+ymin-0.01 << " " << add[j][i] << " " << 0 << endl;
            }
            else if(used[j-1][i+1]==1){
                outputfile << j+xmin-0.01 << " " << i+ymin+0.01 << " " << add[j][i] << " " << 0 << endl;
            }
        }
    }
}

outputfile.close();
}

int main(){
    const char *filename1="53394640_dsm_1m.dat";
    const char *filename2="53394641_dsm_1m.dat";
    const char *filename3="53394630_dsm_1m.dat";
    const char *filename4="53394631_dsm_1m.dat";
    const char *filename5="53394620_dsm_1m.dat";
    const char *filename6="53394621_dsm_1m.dat";
    const char *filename7="53394610_dsm_1m.dat";
    const char *filename8="53394611_dsm_1m.dat";
    write(filename1);
    write(filename2);
    write(filename3);
    write(filename4);
    write(filename5);
    write(filename6);
    write(filename7);
    write(filename8);
}