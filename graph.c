#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <Windows.h>


//�׷��� �ڷᱸ���� ����(Edge) ����(Vertex)���� ������ ����
//��������Ʈ, ��������� ���ؼ� ǥ���� �� ������
//��������Ʈ - ���Ḯ��Ʈ�� ������ �׷����� Insert:O(1), Delete:O(V), Select:O(E)�� �����Ǹ� ��ұ׷���(E>V)�� ����
// ���� : �޸�ȿ��,  ���� : EdgeŽ�� ����
//������� - 2���� �迭�� ������ �׷����� Insert:O(1), Delete:O(1), Select:O(1)�� �����Ǹ� �����׷���(E<V)�� ����
// ���� : EdgeŽ�� ����,  ���� : �޸� ����

//�׷��� ���� 16�� 
/*
	������ - �����̾��� A B������ ������ �Ѵ� �Դٰ��ٰ� ������ �׷��� 
	������ - �������ִ� A B������ ������ A->B�ϰ�� B���� A�� ����	
	����ġ - ������ ����ġ(���)�� �ִ� �׷��� A -> B�� ���� ������ ����� 5�̸� 5�� �Ÿ���ŭ ���� ����	
	���� - ������ ����ġ(���)�� ���� �׷���
	����Ŭ - ó�������� ������������ ���� ��ȯ�ϴ� �׷����� ������ ��� 2�� �̻��� ������ ��������
	�����Ŭ - ��ȯ�� ���ϴ� �׷����� DAG��� �������� ��ݵ� �۾������층 ����� ���� ���� 
				A�۾��� B�۾��� �������̶�� A ���� ó���ϰ� B �ϴ� ������ A->B�׷��� ���¸� ���
	���� - ��� ������ ���� ����� �׷����� ��� ���� ���̿� �ּ� �Ѱ��� *��ΰ� �־� �и��� �κ��� ���� �׷���
				�� ��δ� ������ ����Ǿ�� �Ѵٴ°� �ƴ� A B C�� ������ A-B-C�� �Ǿ��־ ����׷�����
	�񿬰� - � ������ ���� ������� ���� �׷��� ���� ������ �� �ִ� �׷��� A-B C-D ���� ���¸� ���
	���� - ��� ������ ���� �������� ����� �׷��� V = V(V-1)/2�� ������ ����
	��� - ���� < ���� �׷���
	���� - ���� > ���� �׷���
	��� - ����� ������ �������� �ʰ� �׸� �� �ִ� �׷���
	Ʈ�� - ����Ŭ����, ��� ������ ���� ����� �׷��� �� �������� ������ �� �ϳ��� ��θ� �����ϴ� Ư¡�� ����
	��Ƽ - �� ���� ���� ���� ����(���ణ��)�� ������ �� �ִ� �׷��� 
	�κ� - �Ϻ� ������ �������� ������ �׷��� �⺻ �׷����� �Ϻθ� �����ؼ� �����
*/

//��������Ʈ�� �̿��� �⺻ �׷���(������׷���)
//Insert : O(1)�� ������ ������
//Search : O(V)�� ������ �ִ�.
//Ž���� �ʺ� �켱 Ž��(BFS)�� ���� �켱 Ž��(DFS) 2������ ������.
//BFS ����� ������ �������� ���ʴ�� Ž���ϴ� ������� ť�� �̿��ؼ� ����
//DFS �ϳ��� ��θ� ������ Ž���� �� �ٽ� ���ƿͼ� �ٸ� ��θ� Ž���ϴ� ������� ��͸� �̿��Ѵ�.

typedef struct Graph_List_Default_Vertex {	//���� ����
	int Vertex;
	struct Graph_List_Default_Vertex* next;
}Graph_List_Default_Vertex;

typedef struct Graph_List_Default_Graph {	//�׷��� ����
	int numVertices;
	Graph_List_Default_Vertex** adjLists;
	/*
	graph ����ü�� ����Ʈ��
	0 -> ���� -> ���� -> ���� -> NULL
	1 -> ���� -> NULL
	2 -> NULL 
	�̷������� �׷��� ����ü��
	*/
}Graph_List_Default_Graph;

//���� ����
Graph_List_Default_Vertex* Graph_List_Default_createVertex(int v) { 
	Graph_List_Default_Vertex* newVertex = (Graph_List_Default_Vertex*)malloc(sizeof(Graph_List_Default_Vertex));
	newVertex->Vertex = v;
	newVertex->next = NULL;
	return newVertex;
}

//�׷��� ����
Graph_List_Default_Graph* Graph_List_Default_createGraph(int vertices) {
	Graph_List_Default_Graph* graph = (Graph_List_Default_Graph*)malloc(sizeof(Graph_List_Default_Graph));
	graph->numVertices = vertices;	//������ ����
	//������ ���� ���� ����Ʈ
	graph->adjLists = (Graph_List_Default_Vertex*)malloc(sizeof(Graph_List_Default_Vertex*) * vertices);

	//����Ʈ �ʱ�ȭ
	for (int i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
	}
	return graph;
}

//�׷����� ���� �߰�
void Graph_List_Default_addEdge(Graph_List_Default_Graph* graph, int src, int dest) {
	//src�� dest��� ���� �ΰ��� �������� �մ� �Լ�

	//dest������ ����� dest�� src������ �մ� ����
	// dest->src
	Graph_List_Default_Vertex* newVertex = Graph_List_Default_createVertex(dest);
	newVertex->next = graph->adjLists[src];
	graph->adjLists[src] = newVertex;

	//src������ ����� src�� dest������ �մ� ����
	// src->dest
	newVertex = Graph_List_Default_createVertex(src);
	newVertex->next = graph->adjLists[dest];
	graph->adjLists[dest] = newVertex;	
}

//�׷����� Ž�� �ʺ�켱Ž��(BFS)
//��������Ʈ�� BFS�� �ð� ���⵵�� O(V+E)
//�̷��� ������ ���Ҿ� ������ ũ�Ⱑ �þ���� �����ɸ��⿡ ��ұ׷���(����<����)�� �ξ� ȿ����
void Graph_List_Default_BFS(Graph_List_Default_Graph* graph, int startVertex) {
	boolean* visited = (boolean*)malloc(sizeof(boolean) * graph->numVertices);
	for (int i = 0; i < graph->numVertices; i++) visited[i] = 0;
	int* queue = (int*)malloc(sizeof(int) * graph->numVertices);
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFSŽ�� ���� : ");
	while (front != rear) {
		int currentVertex = queue[front++];
		printf("%d ", currentVertex);

		Graph_List_Default_Vertex* temp = graph->adjLists[currentVertex];
		while (temp) {
			int adjVertex = temp->Vertex;
			if (!visited[adjVertex]) {
				visited[adjVertex] = 1;
				queue[rear++] = adjVertex;
			}
			temp = temp->next;
		}
	}
	printf("\n");
	free(queue);
	free(visited);
}

//���� �켱 Ž��(DFS)
//��������Ʈ�� DFS�� �ð����⵵�� O(V+E)
//�̷��� ������ ���Ҿ� ������ ũ�Ⱑ �þ���� �����ɸ��⿡ ��ұ׷���(����<����)�� �ξ� ȿ����
//��͸� �̿��ؼ� Ž���� �迭 visited�� vertex���� �ֱ⿡ ��͸� �̿��ص� ��������
void Graph_List_Default_DFS(Graph_List_Default_Graph* graph, int vertex, boolean visited[]) {
	visited[vertex] = 1;
	printf("%d ", vertex);	

	Graph_List_Default_Vertex* temp = graph->adjLists[vertex];
	while (temp) {
		int adjVertex = temp->Vertex;
		if (!visited[adjVertex]) {
			Graph_List_Default_DFS(graph, adjVertex, visited);
		}
		temp = temp->next;
	}
}

//��������Ʈ���� ���� ���� �����ϰ��� �ϴ� �������� ������ ����
void Graph_List_Default_Delete_Edge(Graph_List_Default_Graph* graph, int start, int end) {
	Graph_List_Default_Vertex* temp = graph->adjLists[start];
	Graph_List_Default_Vertex* prev = NULL;

	//start���� end������ ����
	while (temp != NULL && temp->Vertex != end) {
		prev = temp;
		temp = temp->next;
	}
	if (temp != NULL) {
		if (prev == NULL) {
			graph->adjLists[start] = temp->next;
		}
		else {
			prev->next = temp->next;
		}
		free(temp);
	}

	//�ݴ���� end���� start�� ����
	temp = graph->adjLists[end];
	prev = NULL;
	while (temp != NULL && temp->Vertex != start) {
		prev = temp;
		temp = temp->next;
	}

	if (temp != NULL) {
		if (prev == NULL) {
			graph->adjLists[end] = temp->next;
		}
		else {
			prev->next = temp->next;
		}
		free(temp);
	}
}

//��������
void Graph_List_Default_Delete_Vertex(Graph_List_Default_Graph* graph, int vertex) {
	//�����ϰ��� �ϴ� ������ ����� ��� ���� ����
	for (int i = 0; i < graph->numVertices; i++) {
		if (i != vertex) {
			Graph_List_Default_Delete_Edge(graph, i, vertex);
		}
	}
	
	//���������� ������ ����
	while (graph->adjLists[vertex] != NULL) {
		Graph_List_Default_Vertex* temp = graph->adjLists[vertex];
		graph->adjLists[vertex] = graph->adjLists[vertex]->next;
		free(temp);
	}
}

//���Ἲ���� ã��
//���Ἲ�� - ���� ����Ǿ� �ִ� �������� ���� �κ� �׷��� ������ ���Ἲ���̶�� ��
//A-B-C , D-E �̷����� �׷����� �ִٸ� ���Ἲ���� 2���� ���� ������ �ִ°�
//Ư¡ - ���� ���п� ���� ��� ������ �����ϴ� ��ΰ� �־���ϰ�
//�� �ٸ� ���Ἲ�п� ���� ������ �����ϴ� ��ΰ� ������ �ȵǸ�
//BFS, DFSŽ���� �̿��� ã�´�.
void Graph_List_Default_Connected_Component(Graph_List_Default_Graph* graph, int visited[]) {
	int i;
	int count = 0;
	//DFS�� ������ ���Ἲ���� ������ �ľ��� A-B-C, D-E�� �κп��� �׷����� ������� 
	//A-B-C�� ���Ἲ��1, D-E�� ���Ἲ��2��� �Ͽ� �׷����� � �������� ����Ǿ��ִ��� Ȯ���� �� ����
	for (i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {	//�湮���� �ʴ� ������ �������
			count++;
			Graph_List_Default_DFS(graph, i, visited);
		}
	}
}

//����Ʈ�� - �׷����� ��� ������ �����ϴ� Ʈ���� Ʈ���� Ư���� ���·� ��� �������� ����Ǿ�� �ϸ� ����Ŭ�� �̷�� �ȵȴ�.
//���� �׷��� -> ���� Ʈ���� ����Ŭ���� ��� ������ ������ �����Ű�� Ʈ�������� ����°�
//Ȱ�� - ��ȭ���̵� ��Ʈ��ũ�� ��뿡���� Ư�� �������� �����ϱ� ���� �ּ� ��� ��θ� �����ϴ� ������ ���� ���� �����Ҷ� ���
void Graph_List_Default_DFS_SpanningTree(Graph_List_Default_Graph* graph ,int vertex, int visited[]) {
	//DFS�� �̿��� ����Ʈ�� ��� ����
	visited[vertex] = 1;
	printf("%d ", vertex);
	
	for (int i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {
			Graph_List_Default_Vertex* temp = graph->adjLists[vertex];
			while (temp != NULL) {
				int adjacent = temp->Vertex;
				if (!visited[adjacent]) {
					printf("(%d -> %d)\n", vertex, adjacent);
					Graph_List_Default_DFS(graph, vertex, visited);
					//Graph_List_Default_BFS(graph, vertex, visited);
					//BFS�� �̿��� ����� �ִ�.
				}
				temp = temp->next;
			}
			printf("\n");
		}
	}
}

//�׷��� ���
void Graph_List_Default_printGraph(Graph_List_Default_Graph* graph) {
	for (int v = 0; v < graph->numVertices; v++) {
		Graph_List_Default_Vertex* temp = graph->adjLists[v];
		printf("\n ���� %d: ", v);
		while (temp) {
			printf("%d -> ", temp->Vertex);
			temp = temp->next;
		}
		printf("NULL");
	}
}

void Graph_List_Default_main() {
	int vertices = 6;
	Graph_List_Default_Graph* graph = Graph_List_Default_createGraph(vertices);

	Graph_List_Default_addEdge(graph, 0, 1);
	Graph_List_Default_addEdge(graph, 0, 2);
	Graph_List_Default_addEdge(graph, 0, 3);

	//Graph_List_Default_BFS(graph, 1);
	boolean* visited = (boolean*)malloc(sizeof(boolean) * graph->numVertices);
	for (int i = 0; i < graph->numVertices; i++) visited[i] = 0;
	Graph_List_Default_DFS(graph, 3, visited);

	Graph_List_Default_printGraph(graph);
	free(visited);
}


//��������� �̿��� �⺻ �׷���(������׷���)

#define MAX_VERTICES 10  //�׷����� �ִ� ���� ����

typedef struct Graph_Arr_Default_Graph {
	int numVertices;
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
}Graph_Arr_Default_Graph;

//�׷��� �ʱ�ȭ
void Graph_Arr_Default_initGraph(Graph_Arr_Default_Graph* graph, int vertices) {
	if (vertices > MAX_VERTICES) {
		printf("������ ������ �ʹ� �����ϴ�.");
		return;
	}
	graph->numVertices = vertices;	
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			graph->adjMatrix[i][j] = 0; //������ �������� ������ �ʱⰪ 0
		}
	}
}

//�׷����� Ž�� �ʺ�켱Ž��(BFS)
//������Ľ� BFS�� �ð� ���⵵�� O(V^2)
void Graph_Arr_Default_BFS(Graph_Arr_Default_Graph* graph, int startVertex) {
	//���� ������ ���� �������� �ʺ� Ž���ϸ鼭 �׷����� Ž���س����� ����̴�.
	boolean visited[MAX_VERTICES] = { 0 };//false�� ä��
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFS Ž�� ����: ");
	while (front != rear) {
		int currentVertex = queue[front++];
		printf("%d ", currentVertex);

		for (int i = 0; i < graph->numVertices; i++) {
			if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
				visited[i] = 1;
				queue[rear++] = i;
			}
		}
	}
	printf("\n");
}

//���� �켱 Ž��(DFS)
//��������Ʈ�� DFS�� �ð����⵵�� O(V^2)
//������ ũ��� �ð����⵵�� ������ �����ʱ⿡ �����׷���(����<����)�� ����
void Graph_Arr_Default_DFS(Graph_Arr_Default_Graph* graph, int vertex, boolean visited[]) {
	visited[vertex] = 1;
	printf("%d ", vertex);

	for (int i = 0; i < graph->numVertices; i++) {
		if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
			Graph_Arr_Default_DFS(graph, i, visited);
		}
	}
}

//���� �߰�
void Graph_Arr_Default_addEdge(Graph_Arr_Default_Graph* graph, int start, int end) {
	graph->adjMatrix[start][end] = 1;
	graph->adjMatrix[end][start] = 1;	//�������̴� �ݴ���⵵ ��������
}

//������Ŀ��� ���� ���� �����ϰ��� �ϴ� �������� ������ ����
void Graph_Arr_Default_Delete_Edge(Graph_Arr_Default_Graph* graph, int start, int end) {
	graph->adjMatrix[start][end] = 0;
	graph->adjMatrix[end][start] = 0;
}

//������Ŀ��� ���� ����
void Graph_Arr_Default_Delete_Vertex(Graph_Arr_Default_Graph* graph, int vertex) {
	//�ش� ������ ����� ������ ��� �����ؾ��� ���� ������ ������ �Ǿ�� ��
	for (int i = 0; i < graph->numVertices; i++) {
		graph->adjMatrix[vertex][i] = 0;
		graph->adjMatrix[i][vertex] = 0;
	}
	//�̰͵� ������ ������ ������� ����� �����
}

//���Ἲ���� ã��
//���Ἲ�� - ���� ����Ǿ� �ִ� �������� ���� �κ� �׷��� ������ ���Ἲ���̶�� ��
//A-B-C , D-E �̷����� �׷����� �ִٸ� ���Ἲ���� 2���� ���� ������ �ִ°�
//Ư¡ - ���� ���п� ���� ��� ������ �����ϴ� ��ΰ� �־���ϰ�
//�� �ٸ� ���Ἲ�п� ���� ������ �����ϴ� ��ΰ� ������ �ȵǸ�
//BFS, DFSŽ���� �̿��� ã�´�.
void Graph_Arr_Default_Connected_Component(Graph_Arr_Default_Graph* graph, int visited[]) {
	int i;
	int count = 0;
	//DFS�� ������ ���Ἲ���� ������ �ľ��� A-B-C, D-E�� �κп��� �׷����� ������� 
	//A-B-C�� ���Ἲ��1, D-E�� ���Ἲ��2��� �Ͽ� �׷����� � �������� ����Ǿ��ִ��� Ȯ���� �� ����
	for (i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {	//�湮���� �ʴ� ������ �������
			count++;
			Graph_Arr_Default_DFS(graph, i, visited);
		}
	}
}

//����Ʈ�� - �׷����� ��� ������ �����ϴ� Ʈ���� Ʈ���� Ư���� ���·� ��� �������� ����Ǿ�� �ϸ� ����Ŭ�� �̷�� �ȵȴ�.
//���� �׷��� -> ���� Ʈ���� ����Ŭ���� ��� ������ ������ �����Ű�� Ʈ�������� ����°�
//Ȱ�� - ��ȭ���̵� ��Ʈ��ũ�� ��뿡���� Ư�� �������� �����ϱ� ���� �ּ� ��� ��θ� �����ϴ� ������ ���� ���� �����Ҷ� ���
void Graph_Arr_Default_DFS_SpanningTree(Graph_Arr_Default_Graph* graph, int vertex, int visited[]) {
	//DFS�� �̿��� ����Ʈ�� ��� ����
	visited[vertex] = 1;
	printf("%d ", vertex);

	for (int i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {
			for (int i = 0; i < graph->numVertices; i++) {
				if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
					printf("(%d -> %d)\n", vertex, i);
					Graph_Arr_Default_DFS(graph, vertex, visited);
					//Graph_Arr_Default_BFS(graph, vertex, visited);
					//BFS�� �̿��� ����� �ִ�.
				}
			}
		}
	}
}

//�׷��� ���
void Graph_Arr_Default_printGraph(Graph_Arr_Default_Graph* graph) {
	for (int i = 0; i < graph->numVertices; i++) {
		for (int j = 0; j < graph->numVertices; j++) {
			printf("%d ", graph->adjMatrix[i][j]);
		}
		printf("\n");
	}
}

void Graph_Arr_Default_main() {
	Graph_Arr_Default_Graph graph;

	Graph_Arr_Default_initGraph(&graph, 5);

	Graph_Arr_Default_addEdge(&graph, 0, 1);
	Graph_Arr_Default_addEdge(&graph, 0, 2);
	
	Graph_Arr_Default_addEdge(&graph, 0, 4);

	//Graph_Arr_Default_BFS(&graph, 1);
	boolean* visited = (boolean*)malloc(sizeof(boolean) * graph.numVertices);
	for (int i = 0; i < graph.numVertices; i++) visited[i] = 0;

	Graph_Arr_Default_DFS(&graph, 4, visited);
	printf("\n");

	Graph_Arr_Default_printGraph(&graph);
}


//���ݱ����� �׷����� �ܼ� �׷����� ���� ������ ���� ������ ���Ḹ �Ǿ��ִ°����� �����ϴ� �⺻ �׷����� ������ �ʴ´�.
//�̹��� ���� �׷������� �ܼ� �׷����� �ƴ� �׷����� �������� ����� ������ ���Ž���� ������ ���ϴ� ������ �����Ѵ�.

//��������Ʈ�� ������ ����� �����ϴ� �׷��� ����
typedef struct Graph_List_Weight_Edge {
	int vertex; //�������� ����
	int weight; //�� ������ ����ġ ���
	struct Graph_List_Weight_Edge* next;	//�ٸ� ������ ����Ű�� ������ ��������Ʈ
}Graph_List_Weight_Edge;

typedef struct Graph_List_Weight_Vertex {
	struct Graph_List_Weight_Edge* head; //���� ����Ʈ�� ����
}Graph_List_Weight_Vertex;

typedef struct Graph_List_Weight_Graph {
	int numVertices; //������ ����
	struct Graph_List_Weight_Vertex** vertices;		//���� ����Ʈ
}Graph_List_Weight_Graph;

//���� ����
void Graph_List_Weight_createVertex(Graph_List_Weight_Graph* graph) {
	Graph_List_Weight_Vertex* vertex = (Graph_List_Weight_Vertex*)malloc(sizeof(Graph_List_Weight_Vertex));
	for (int i = 0; i < graph->numVertices; i++) {
		graph->vertices[i] = vertex;
		vertex = (Graph_List_Weight_Vertex*)malloc(sizeof(Graph_List_Weight_Vertex));
	}
}

//�׷��� �ʱ�ȭ
Graph_List_Weight_Graph* Graph_List_Weight_createGraph(int numVertices) {
	Graph_List_Weight_Graph* graph = (Graph_List_Weight_Graph*)malloc(sizeof(Graph_List_Weight_Graph));
	graph->numVertices = numVertices;

	graph->vertices = (Graph_List_Weight_Vertex*)malloc(sizeof(Graph_List_Weight_Vertex) * numVertices);

	//������ �����ϰ� ������ ����Ű�� ���������� NULL�� �ʱ�ȭ����
	Graph_List_Weight_createVertex(graph);
	for (int i = 0; i < numVertices; i++) {
		graph->vertices[i]->head = NULL;
	}

	return graph;
}

//���� �߰� �Լ�(�����)
void Graph_List_Weight_addEdge(Graph_List_Weight_Graph* graph, int src, int dest, int weight) {
	//src�� dest��� �ΰ��� ������ ����� ����ġ weight�� ���ؼ� ���� ������ �������ָ� �ȴ�.
	Graph_List_Weight_Edge* edge = (Graph_List_Weight_Edge*)malloc(sizeof(Graph_List_Weight_Edge));
	edge->vertex = dest;
	edge->weight = weight;
	edge->next = graph->vertices[src]->head;	//������ ����Ű�� ����src�� ���� ��������Ʈ�� ����
	graph->vertices[src]->head = edge;		//���� ��������Ʈ�� ����

	edge = (Graph_List_Weight_Edge*)malloc(sizeof(Graph_List_Weight_Edge));
	edge->vertex = src;
	edge->weight = weight;
	edge->next = graph->vertices[dest]->head;	//������ ����Ű�� ���� dest�� ���� ���� ����Ʈ�� ����
	graph->vertices[dest]->head = edge;		//���� ��������Ʈ�� ����
}

//�׷����� Ž�� �ʺ�켱Ž��(BFS)
//��������Ʈ�� BFS�� �ð� ���⵵�� O(V+E)
//�̷��� ������ ���Ҿ� ������ ũ�Ⱑ �þ���� �����ɸ��⿡ ��ұ׷���(����<����)�� �ξ� ȿ����
void Graph_List_Weight_BFS(Graph_List_Weight_Graph* graph, int startVertex) {
	boolean* visited = (boolean*)malloc(sizeof(boolean) * graph->numVertices);
	for (int i = 0; i < graph->numVertices; i++) visited[i] = 0;

	int* queue = (int*)malloc(sizeof(int) * graph->numVertices);
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFSŽ�� ���� : ");
	while (front != rear) {
		int currentVertex = queue[front++];
		printf("%d ", currentVertex);

		Graph_List_Weight_Edge* temp = graph->vertices[currentVertex]->head;
		while (temp) {
			int adjVertex = temp->vertex;
			if (!visited[adjVertex]) {
				visited[adjVertex] = 1;
				queue[rear++] = adjVertex;
			}
			temp = temp->next;
		}
	}
	printf("\n");
	free(queue);
	free(visited);
}

//���� �켱 Ž��(DFS)
//��������Ʈ�� DFS�� �ð����⵵�� O(V+E)
//�̷��� ������ ���Ҿ� ������ ũ�Ⱑ �þ���� �����ɸ��⿡ ��ұ׷���(����<����)�� �ξ� ȿ����
//��͸� �̿��ؼ� Ž���� �迭 visited�� vertex���� �ֱ⿡ ��͸� �̿��ص� ��������
void Graph_List_Weight_DFS(Graph_List_Weight_Graph* graph, int vertex, boolean visited[]) {
	visited[vertex] = 1;
	printf("%d ", vertex);

	Graph_List_Weight_Edge* temp = graph->vertices[vertex]->head;
	while (temp) {
		int adjVertex = temp->vertex;
		if (!visited[adjVertex]) {
			Graph_List_Weight_DFS(graph, adjVertex, visited);
		}
		temp = temp->next;
	}
}

//�׷��� ��� �Լ�
void Graph_List_Weight_print(Graph_List_Weight_Graph* graph) {
	for (int i = 0; i < graph->numVertices; i++) {
		Graph_List_Weight_Edge* temp = graph->vertices[i]->head;
		printf("Vertex %d : ", i);
		while (temp) {
			printf(" -> %d (Weight: %d)", temp->vertex, temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}
}

void Graph_List_Weight_main() {
	int numVertices = 3;
	Graph_List_Weight_Graph* graph = Graph_List_Weight_createGraph(numVertices);

	Graph_List_Weight_addEdge(graph, 0, 1, 2);
	Graph_List_Weight_addEdge(graph, 0, 2, 5);
	//Graph_List_Weight_addEdge(graph, 1, 2, 2);

	Graph_List_Weight_print(graph);

	//Graph_List_Weight_BFS(graph, 0);
	boolean* visited = (boolean*)malloc(sizeof(boolean) * numVertices);
	for (int i = 0; i < numVertices; i++) visited[i] = 0;
	Graph_List_Weight_DFS(graph, 2,visited);

}

//������Ŀ� ����� �߰��� �׷���
typedef struct Graph_Arr_Weight_Graph {
	int numVertices;
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
}Graph_Arr_Weight_Graph;

//�׷��� �ʱ�ȭ
void Graph_Arr_Weight_initGraph(Graph_Arr_Weight_Graph* graph, int vertices) {
	if (vertices > MAX_VERTICES) {
		printf("������ ������ �ʹ� �����ϴ�.");
		return;
	}
	graph->numVertices = vertices;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			graph->adjMatrix[i][j] = 0; //������ �������� ������ �ʱⰪ 0
		}
	}
}

//���� �߰�
void Graph_Arr_Weight_addEdge(Graph_Arr_Weight_Graph* graph, int dest, int src, int weight) {
	graph->adjMatrix[dest][src] = weight;
	graph->adjMatrix[src][dest] = weight;
}

void Graph_Arr_Weight_print(Graph_Arr_Weight_Graph* graph) {
	for (int i = 0; i < graph->numVertices; i++) {
		for (int j = 0; j < graph->numVertices; j++) {
			if (graph->adjMatrix[i][j] == 0) {
				printf("%d ", 0);
			}
			else {
				printf("%d ", graph->adjMatrix[i][j]);
			}
		}
		printf("\n");
	}
}

//�׷����� Ž�� �ʺ�켱Ž��(BFS)
//������Ľ� BFS�� �ð� ���⵵�� O(V^2)
void Graph_Arr_Weight_BFS(Graph_Arr_Weight_Graph* graph, int startVertex) {
	//���� ������ ���� �������� �ʺ� Ž���ϸ鼭 �׷����� Ž���س����� ����̴�.
	boolean visited[MAX_VERTICES] = { 0 };//false�� ä��
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFS Ž�� ����: ");
	while (front != rear) {
		int currentVertex = queue[front++];
		printf("%d ", currentVertex);

		for (int i = 0; i < graph->numVertices; i++) {
			if (graph->adjMatrix[currentVertex][i] >= 1 && !visited[i]) {
				visited[i] = 1;
				queue[rear++] = i;
			}
		}
	}
	printf("\n");
}

//���� �켱 Ž��(DFS)
//��������Ʈ�� DFS�� �ð����⵵�� O(V^2)
//������ ũ��� �ð����⵵�� ������ �����ʱ⿡ �����׷���(����<����)�� ����
void Graph_Arr_Weight_DFS(Graph_Arr_Weight_Graph* graph, int vertex, boolean visited[]) {
	visited[vertex] = 1;
	printf("%d ", vertex);

	for (int i = 0; i < graph->numVertices; i++) {
		if (graph->adjMatrix[vertex][i] >= 1 && !visited[i]) {
			Graph_Arr_Weight_DFS(graph, i, visited);
		}
	}
}

void Graph_Arr_Weight_main() {
	Graph_Arr_Weight_Graph graph;
	int verNum = 5;
	Graph_Arr_Weight_initGraph(&graph, verNum);

	Graph_Arr_Weight_addEdge(&graph, 0, 1, 5);
	Graph_Arr_Weight_addEdge(&graph, 0, 2, 7);
	Graph_Arr_Weight_addEdge(&graph, 0, 3, 10);

	Graph_Arr_Weight_print(&graph);

	//Graph_Arr_Weight_BFS(&graph, 3); 

	boolean* visited = (boolean*)malloc(sizeof(boolean) * verNum);
	for (int i = 0; i < verNum; i++) visited[i] = 0;

	Graph_Arr_Weight_DFS(&graph, 3,visited); 
}

//�ּҺ�����Ʈ��
//�ִܰ��
//�������� 
//�� 3������ ���߿� �˰��� �����Ҷ� ����