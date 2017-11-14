
#include"useful/useful_utils.h"
//#include"neighbor_joining.h"
#include"Graph_Node.h"
#include"time.h"

int main()
{
	int i,j;

	
	Graph_Node* a= new Graph_Node(1);
	Graph_Node* b= new Graph_Node(2);
	Graph_Node* c= new Graph_Node(3);
	Graph_Node* d= new Graph_Node(4);
	Graph_Node* e= new Graph_Node(5);
	Graph_Node* k= new Graph_Node(6);
	Graph_Node* l;//= new Graph_Node(7);

	a->insertConnection(b,1);
	a->insertConnection(c,1);
	c->insertConnection(e,1);
	c->insertConnection(d);
	e->insertConnection(k);
	//e->insertConnection(l);

	c->insertConnection(d,1);
	
	//printf("n %d\n",a->treeHeight());

	a->print();


	/*int n=10;
	Graph_Node** tree= (Graph_Node**)malloc(sizeof(Graph_Node*)*n);

	for(i=0;i<n;i++)
		tree[i]= new Graph_Node();


	tree->print();
*/
/*	a->print();

	//a->deleteTree();
	
	//a->print();

	*/

	/*
	
	int n=6;

	srand(time(NULL));

	float **distance_matrix=(float **)malloc(sizeof(float*)*n);
	for(i=0;i<n;i++)
	{
		distance_matrix[i]= (float*)malloc(sizeof(float)*n);
		for(j=0;j<n;j++)
		{
			//distance_matrix[i][j]=0.0f;//xrand(0,1);
			distance_matrix[i][j]=xrand(0,1);
		}
	}

	
	distance_matrix[1][0]=5;
	distance_matrix[2][0]=4;
	distance_matrix[2][1]=7;
	distance_matrix[3][0]=7;
	distance_matrix[3][1]=10;
	distance_matrix[3][2]=7;
	distance_matrix[4][0]=6;
	distance_matrix[4][1]=9;
	distance_matrix[4][2]=6;
	distance_matrix[4][3]=5;
	distance_matrix[5][0]=8;
	distance_matrix[5][1]=11;
	distance_matrix[5][2]=8;
	distance_matrix[5][3]=9;
	distance_matrix[5][4]=8;

	

	Graph_Node* tree= neighborJoining(distance_matrix,n);
	
	tree->print();
	
*/

	return 0;
}


