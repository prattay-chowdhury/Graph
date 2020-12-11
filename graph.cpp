//Submitted by Prattay Chowdhury
//Here graph is represented by adjacency matrix 

#include<iostream>
#include<queue>
using namespace std;


class graph
{
private:
  int vertex_count;
  int* in_degree;
  bool** adjacency_matrix;
  bool* visited;
  bool* done;
  char* vertex_val;
  queue<int> q;
  queue<char> BFS_top_order;  //to store final order 
  int rank;
  bool cycle;
  char* DFS_top_order; //to store final order
  
public:
  graph(int v_count,char* val, char* top);
  void add_edge(char i, char j);
  void print_vertices();
  void print_edges();
  void print_in_degree();
  void DFS(int start_index);
  void print_DFS_top_order();
  void reset();
  void BFS();
  void print_BFS_top_order();
};


graph::graph(int v_count, char* val, char *top)
{
   cycle=0;  //flag to check cycle in DFS
   rank=v_count;
//creating empty adjencey matrix with the dimention of vertex count	
	vertex_count=v_count;
  in_degree = new int[vertex_count];
  for(int i=0; i<vertex_count; i++){
	  in_degree[i]=0;
  }
  adjacency_matrix = new bool*[vertex_count];
  for(int i=0; i<vertex_count; i++){
    adjacency_matrix[i] = new bool[vertex_count];
    for(int j=0; j<vertex_count; j++)
      adjacency_matrix[i][j] = 0;
  }
  vertex_val = val;
  DFS_top_order= top;
  //creating empty visit and done flag
  visited = new bool[vertex_count];
  done= new bool[vertex_count];
  for(int k=0; k<vertex_count; k++){
	done[k]=0;
    visited[k]=0;
  }
}

void graph::add_edge(char first, char last){
	int i,j;
for (int k=0; k<vertex_count; k++){
	if (vertex_val[k]==first)
		i=k;
	if (vertex_val[k]==last)
		j=k;
}	
//changing value in adjencent matrix to create edge and changin in degree of vertices
    adjacency_matrix[i][j]=1;
	in_degree[j]++;
  
}

void graph::print_vertices(){
  for(int i=0; i<vertex_count; i++){
    cout << vertex_val[i]<<' ';
  }
  
  cout << endl;
}

void graph::print_edges(){
  for(int i=0; i<vertex_count; i++){
    for(int j=i; j<vertex_count; j++){
      if(adjacency_matrix[i][j]==1)
        cout << '(' << vertex_val[i] << ',' << vertex_val[j] <<')' << ' ';
    }
  }
  cout << endl;
}


void graph::DFS(int start_index){

  int i=start_index;
  	for (i=start_index; i<vertex_count; i++)  
	{     
	if (visited[i]==0) {
		  visited[i]=1;
		  for(int j=0; j<vertex_count; j++){
			if(adjacency_matrix[i][j]==1  && visited[j]==1 && done[j]==0 && i==start_index){
				cycle=1;  //Cycle detected
				break;
			}
			if(adjacency_matrix[i][j]==1 && visited[j]==0 && done[j]==0){
			  DFS(j);
			}
		  }

		  DFS_top_order[rank-1]=vertex_val[i];
		  done[i]=1;
		  rank--;

	}
	}
  
}



void graph:: print_DFS_top_order(){
	if (cycle==0){
	for(int i=0; i<vertex_count; i++){
    cout <<(i+1)<<'-'<<DFS_top_order[i]<<' ';
  }
	}
	else cout<<"There is a cycle in the graph";
  cout<<endl;
}


void graph::reset(){
	cycle=0;
	rank=vertex_count;
	for (int i=0; i<vertex_count; i++){
		visited[i]=0;
		done[i]=0;
	}
}




void graph::BFS(){
	int j;
	
	
	
	for (int i=0; i<vertex_count;i++)
		if(in_degree[i]==0 && visited[i]==0)
		{	q.push(i);
			visited[i]=1; 
		}

	if(q.empty())
		return;		
	
	while (!q.empty())
	{
		j=q.front();
		q.pop();
		BFS_top_order.push(vertex_val[j]);
		for (int k=0; k<vertex_count;k++){
			if (adjacency_matrix[j][k]==1 && visited[k]==0){
				in_degree[k]--;
			}
		}
	}
	BFS();
	
}

void graph::print_BFS_top_order(){
	int size;
	int i=1;
	size=BFS_top_order.size();
	if (size==vertex_count)
		while(!BFS_top_order.empty())
		{
			cout<<i<<"-"<<BFS_top_order.front()<<" ";
			BFS_top_order.pop();
			i++;
		}
	else cout<<"There is a cycle in the graph";
}


int main()
{
  //first graph
  char val_A[14] = {'m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 
  char top_order_A[14];
  graph A(14, &val_A[0],&top_order_A[0]);
  A.add_edge('m','x');
  A.add_edge('m','q');
  A.add_edge('m','r');
  A.add_edge('n','q');
  A.add_edge('n','u');
  A.add_edge('n','o');
  A.add_edge('o','r');
  A.add_edge('o','v');
  A.add_edge('o','s');
  A.add_edge('p','o');
  A.add_edge('p','s');
  A.add_edge('p','z');
  A.add_edge('q','t');
  A.add_edge('r','u');
  A.add_edge('r','y');
  A.add_edge('s','r');
  A.add_edge('u','t');
  A.add_edge('v','x');
  A.add_edge('v','w');
  A.add_edge('w','z');
  A.add_edge('y','v');
  
  

  

  cout << "Vertices in the graph-1: "<<endl;
  A.print_vertices();
  cout << endl << endl;
  
  cout << "Edges in the graph graph-1: "<<endl;
  A.print_edges();
  cout << endl << endl;
  
 
  cout << "DFS topological order of graph-1:"<<endl;
  A.DFS(0);  //starts from index 0
  A.print_DFS_top_order();
  cout << endl << endl;

  A.reset();
  
  cout << "BFS topological order of graph-1:"<<endl;
  A.BFS();
  A.print_BFS_top_order(); 
  cout<<endl<<endl;
  
  
  //Second graph
  char val_B[8]={'1','2','3','4','5','6','7','8'};
  char top_order_B[8];
  graph B(8, &val_B[0],&top_order_B[0]);
  B.add_edge('1','2');
  B.add_edge('1','5');
  B.add_edge('1','6');
  B.add_edge('2','3');
  B.add_edge('2','5');
  B.add_edge('2','7');
  B.add_edge('3','4');
  B.add_edge('4','5');
  B.add_edge('5','7');
  B.add_edge('5','8');
  B.add_edge('6','5');
  B.add_edge('6','8');
  B.add_edge('7','4');
  B.add_edge('7','8');
  
  cout << "Vertices in the graph-2: "<<endl;
  B.print_vertices();
  cout << endl << endl;
  
  cout << "Edges in the graph graph-2: "<<endl;
  B.print_edges();
  cout << endl << endl;
 
 
  cout << "DFS topological order of graph-2:"<<endl;
  B.DFS(0); //starts from index 0
  B.print_DFS_top_order();
  cout << endl << endl;  
	
  B.reset();
  
  cout << "BFS topological order of graph-1:"<<endl;
  B.BFS();
  B.print_BFS_top_order();
  cout<<endl<<endl;
  
  return 0;
}
