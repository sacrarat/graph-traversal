#include <iostream>
#include <string>
#include <assert.h>
#include <utility>
#include <list>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

typedef pair<int,int> node; //distance then id
typedef vector<node> neighbours;

class Graph{

    int vertices;
    public:
        Graph(int v);
        void shortestPath(int u,vector< vector< pair <int,int> > > &adjacency_list,vector<int>& mindistance);

};

Graph::Graph(int v){
    vertices=v;
}

//shortest path using Djikstra algorithm with priority queue
void Graph::shortestPath(int u,vector< vector< pair <int,int> > > &adjacency_list,vector<int>& mindistance){
    mindistance.resize(adjacency_list.size(),numeric_limits<int>::max());
    mindistance[u]=0;

    set< pair<int,int> > PQ;
    PQ.insert(make_pair(mindistance[u],u));

    while (!PQ.empty()){
        int distance=PQ.begin()->first;
        int vertex_u=PQ.begin()->second;
        PQ.erase(PQ.begin());

        vector<node> &surrounding=adjacency_list[vertex_u];
        for (vector<node>::iterator it2=surrounding.begin();it2!=surrounding.end();it2++)
        {
            int vertex_v=(*it2).first;
            int weight=(*it2).second;

            int distance_via_vertex_u=distance+weight;
            if(distance_via_vertex_u<mindistance[vertex_v]){
                PQ.erase(make_pair(mindistance[vertex_v],vertex_v));
                mindistance[vertex_v]=distance_via_vertex_u;
                PQ.insert(make_pair(mindistance[vertex_v],vertex_v));
            }

        }
    }


}

//Finding the shortest path from source to destination
void NearestDriver(){
    int n, m;

    cin >> n >> m;

    Graph g(n); 

     vector< vector< pair <int,int> > > adjacency_list(n);

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;

        adjacency_list[a].push_back(make_pair(b, w));
        adjacency_list[b].push_back(make_pair(a, w));
    }

    vector<int> mindistance;

    int u;
    cin >> u;
    g.shortestPath(u,adjacency_list,mindistance);

    vector<int> v_values;
    vector<int> v_d_values;
    int bestv = -1;
    int l;
    cin >> l;
    for(int i = 0; i < l; i++){
        // scan over every car to get the final answer
        int car_position=0;
        cin>>car_position;

        if(mindistance[car_position]==numeric_limits<int>::max()){
            continue;
        }else{
                v_values.push_back(car_position);
                v_d_values.push_back(mindistance[car_position]);
        }
    }

    int lowest_d=numeric_limits<int>::max();
    int lowest_d_index=0;
    for (int j=0; j<v_values.size();++j){
        if (v_d_values[j]<lowest_d){
            lowest_d=v_d_values[j];
            lowest_d_index=v_values[j];
        }

    }

    int counter=0;
    vector<int> same_distance_v;
    for (int k=0; k<v_d_values.size();++k){
        if (v_d_values[k]==lowest_d){
            ++counter;
            same_distance_v.push_back(v_values[k]);
        }
    }

    if (counter==1){
        bestv=lowest_d_index;
    }else if(counter>1){
        bestv=*min_element(same_distance_v.begin(),same_distance_v.end());
    }

    if(bestv == -1)
        cout << "NO" << endl;
    else
        cout << bestv << endl;
    return;
}

//Finding the cost for shortest path traversal from a batch of source and destination inputs 
void QueryPrice(){
    int n, m;

    cin >> n >> m;

    Graph g(n); 

    vector< vector< pair <int,int> > > adjacency_list(n);

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;

        adjacency_list[a].push_back(make_pair(b, w));
        adjacency_list[b].push_back(make_pair(a, w));
    }

    vector<int> mindistance;
    vector<int> answers;
    vector< vector <int> > solution_map (n);

    for(int i = 0; i < n; ++i){
        g.shortestPath(i,adjacency_list,mindistance);
        for (int j=0; j<mindistance.size();++j){
            solution_map[i].push_back(mindistance[j]);
        }
        mindistance.clear();
    }

    int cost=-1;
    int k;
    cin >>k;
    for(int i = 0; i < k; i++){
        int s,t;
        cin >> s >> t;
        if(solution_map[s][t]==numeric_limits<int>::max()){
            cost=-1;
            answers.push_back(cost);
        }else{
            cost=solution_map[s][t];
            answers.push_back(cost);
        }
    }

    for(int j=0; j<answers.size();j++){
        if (answers[j]==-1){
            cout<<"NO" << endl;
        }else{
            cout << answers[j] <<endl;
        }
    }

}

//Finding the exact diameter of a graph
void Diameter(){
    int n, m;

    cin >> n >> m;

    Graph g(n); 

    vector< vector< pair <int,int> > > adjacency_list(n);

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;

        adjacency_list[a].push_back(make_pair(b, w));
        adjacency_list[b].push_back(make_pair(a, w));
    }

    vector<int> mindistance;
    vector<int> max_values; //maximum values in mindistance for each vertex
    for (int i=0; i<n; ++i){
        g.shortestPath(i,adjacency_list,mindistance);
        max_values.push_back(*max_element(mindistance.begin(),mindistance.end()));
        mindistance.clear();
    }

    if (*max_element(max_values.begin(),max_values.end())==numeric_limits<int>::max()){
        cout << "INF";
    }else{
        cout << *max_element(max_values.begin(),max_values.end());
    }
}

//Finding the approximate diameter of a graph
void DiameterApproximation(){
    int n, m;

    cin >> n >> m;

    Graph g(n);

    vector< vector< pair <int,int> > > adjacency_list(n);

    int a,b,w;
    for(int i = 0; i < m; i++){
        cin >> a >> b >> w;

        adjacency_list[a].push_back(make_pair(b, w));
        adjacency_list[b].push_back(make_pair(a, w));
    }

    vector<int> mindistance;
    g.shortestPath(a,adjacency_list,mindistance);
    int dia_a= *max_element(mindistance.begin(),mindistance.end());
    int u;
    for (int i=0; i< mindistance.size();++i){
        if ((mindistance[i]==dia_a)&&(dia_a!=numeric_limits<int>::max()))
            u=i;
    }
    mindistance.clear();
    int dia_b;
    if (dia_a==numeric_limits<int>::max())
    {
        dia_b=numeric_limits<int>::max();
    }else{
        g.shortestPath(u,adjacency_list,mindistance);
        dia_b= *max_element(mindistance.begin(),mindistance.end());
    }
    if(dia_b==numeric_limits<int>::max()){
        cout << "INF" << endl;
    }else{
        cout << dia_b;
    }
}

int main(){
    string section;
    cin >> section;

    if(section == "NearestDriver")
        NearestDriver();
    else if(section == "QueryPrice")
        QueryPrice();
    else if(section == "Diameter")
        Diameter();
    else if(section == "DiameterApproximation")
        DiameterApproximation();
    else{
        cout << "wrong input file!" << endl;
        assert(0);
    }

    return 0;
}
