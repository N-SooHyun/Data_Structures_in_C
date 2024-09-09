#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <Windows.h>


//그래프 자료구조는 간선(Edge) 정점(Vertex)으로 나누어 지며
//인접리스트, 인접행렬을 통해서 표현할 수 있으며
//인접리스트 - 연결리스트로 구현된 그래프로 Insert:O(1), Delete:O(V), Select:O(E)로 구현되며 희소그래프(E>V)에 적합
// 장점 : 메모리효율,  단점 : Edge탐색 느림
//인접행렬 - 2차원 배열로 구현된 그래프로 Insert:O(1), Delete:O(1), Select:O(1)로 구현되며 밀접그래프(E<V)에 적합
// 장점 : Edge탐색 빠름,  단점 : 메모리 낭비

//그래프 종류 16개 
/*
	무방향 - 방향이없는 A B정점이 있을시 둘다 왔다갔다가 가능한 그래프 
	유방향 - 방향이있는 A B정점에 간선이 A->B일경우 B에서 A는 못감	
	가중치 - 간선에 가중치(비용)이 있는 그래프 A -> B로 갈때 간선의 비용이 5이면 5의 거리만큼 가는 느낌	
	비가중 - 간선에 가중치(비용)가 없는 그래프
	싸이클 - 처음정점은 마지막정점과 같은 순환하는 그래프로 정점은 적어도 2개 이상의 간선을 가져야함
	비싸이클 - 순환을 안하는 그래프로 DAG라는 의존성에 기반된 작업스케쥴링 기법에 많이 쓰임 
				A작업이 B작업에 의존적이라면 A 부터 처리하고 B 하는 식으로 A->B그래프 형태를 띄움
	연결 - 모든 정점이 서로 연결된 그래프로 모든 정점 사이에 최소 한개의 *경로가 있어 분리된 부분이 없는 그래프
				이 경로는 간선이 연결되어야 한다는건 아님 A B C의 정점이 A-B-C로 되어있어도 연결그래프임
	비연결 - 어떤 정점이 서로 연결되지 않은 그래프 고립이 존재할 수 있는 그래프 A-B C-D 같은 형태를 띈다
	완전 - 모든 정점이 전부 간선으로 연결된 그래프 V = V(V-1)/2의 간선을 가짐
	희소 - 정점 < 간선 그래프
	밀집 - 정점 > 간선 그래프
	평면 - 평면위 간선이 교차하지 않고 그릴 수 있는 그래프
	트리 - 싸이클없고, 모든 정점이 서로 연결된 그래프 두 정점간에 간선은 단 하나의 경로만 존재하는 특징을 가짐
	멀티 - 두 정점 간에 여러 간선(평행간선)이 존재할 수 있는 그래프 
	부분 - 일부 정점과 간선으로 구성된 그래프 기본 그래프의 일부만 발췌해서 만든것
*/

//인접리스트를 이용한 기본 그래프(무방향그래프)
//Insert : O(1)을 가지고 있으며
//Search : O(V)을 가지고 있다.
//탐색은 너비 우선 탐색(BFS)과 깊이 우선 탐색(DFS) 2가지로 나뉜다.
//BFS 가까운 정점을 기준으로 차례대로 탐색하는 방식으로 큐를 이용해서 구현
//DFS 하나의 경로를 끝까지 탐색한 후 다시 돌아와서 다른 경로를 탐색하는 방식으로 재귀를 이용한다.

typedef struct Graph_List_Default_Vertex {	//정점 구조
	int Vertex;
	struct Graph_List_Default_Vertex* next;
}Graph_List_Default_Vertex;

typedef struct Graph_List_Default_Graph {	//그래프 구조
	int numVertices;
	Graph_List_Default_Vertex** adjLists;
	/*
	graph 구조체의 리스트는
	0 -> 정점 -> 정점 -> 정점 -> NULL
	1 -> 정점 -> NULL
	2 -> NULL 
	이런느낌의 그래프 구조체임
	*/
}Graph_List_Default_Graph;

//정점 생성
Graph_List_Default_Vertex* Graph_List_Default_createVertex(int v) { 
	Graph_List_Default_Vertex* newVertex = (Graph_List_Default_Vertex*)malloc(sizeof(Graph_List_Default_Vertex));
	newVertex->Vertex = v;
	newVertex->next = NULL;
	return newVertex;
}

//그래프 생성
Graph_List_Default_Graph* Graph_List_Default_createGraph(int vertices) {
	Graph_List_Default_Graph* graph = (Graph_List_Default_Graph*)malloc(sizeof(Graph_List_Default_Graph));
	graph->numVertices = vertices;	//정점의 개수
	//정점에 대한 인접 리스트
	graph->adjLists = (Graph_List_Default_Vertex*)malloc(sizeof(Graph_List_Default_Vertex*) * vertices);

	//리스트 초기화
	for (int i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
	}
	return graph;
}

//그래프에 간선 추가
void Graph_List_Default_addEdge(Graph_List_Default_Graph* graph, int src, int dest) {
	//src와 dest라는 정점 두개를 간선으로 잇는 함수

	//dest정점을 만들고 dest에 src정점을 잇는 영역
	// dest->src
	Graph_List_Default_Vertex* newVertex = Graph_List_Default_createVertex(dest);
	newVertex->next = graph->adjLists[src];
	graph->adjLists[src] = newVertex;

	//src정점을 만들고 src에 dest정점을 잇는 영역
	// src->dest
	newVertex = Graph_List_Default_createVertex(src);
	newVertex->next = graph->adjLists[dest];
	graph->adjLists[dest] = newVertex;	
}

//그래프의 탐색 너비우선탐색(BFS)
//인접리스트시 BFS의 시간 복잡도는 O(V+E)
//이렇듯 정점과 더불어 간선의 크기가 늘어날수록 오래걸리기에 희소그래프(간선<정점)에 훨씬 효율적
void Graph_List_Default_BFS(Graph_List_Default_Graph* graph, int startVertex) {
	boolean* visited = (boolean*)malloc(sizeof(boolean) * graph->numVertices);
	for (int i = 0; i < graph->numVertices; i++) visited[i] = 0;
	int* queue = (int*)malloc(sizeof(int) * graph->numVertices);
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFS탐색 순서 : ");
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

//깊이 우선 탐색(DFS)
//인접리스트시 DFS의 시간복잡도는 O(V+E)
//이렇듯 정점과 더불어 간선의 크기가 늘어날수록 오래걸리기에 희소그래프(간선<정점)에 훨씬 효율적
//재귀를 이용해서 탐색함 배열 visited에 vertex값을 넣기에 재귀를 이용해도 문제없음
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

//인접리스트에서 간선 삭제 삭제하고자 하는 정점간의 간선을 지움
void Graph_List_Default_Delete_Edge(Graph_List_Default_Graph* graph, int start, int end) {
	Graph_List_Default_Vertex* temp = graph->adjLists[start];
	Graph_List_Default_Vertex* prev = NULL;

	//start에서 end정점을 삭제
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

	//반대방향 end에서 start를 삭제
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

//정점삭제
void Graph_List_Default_Delete_Vertex(Graph_List_Default_Graph* graph, int vertex) {
	//삭제하고자 하는 정점과 연결된 모든 간선 제거
	for (int i = 0; i < graph->numVertices; i++) {
		if (i != vertex) {
			Graph_List_Default_Delete_Edge(graph, i, vertex);
		}
	}
	
	//최종적으로 정점을 제거
	while (graph->adjLists[vertex] != NULL) {
		Graph_List_Default_Vertex* temp = graph->adjLists[vertex];
		graph->adjLists[vertex] = graph->adjLists[vertex]->next;
		free(temp);
	}
}

//연결성분을 찾기
//연결성분 - 서로 연결되어 있는 여러개의 고립된 부분 그래프 각각을 연결성분이라고 함
//A-B-C , D-E 이런식의 그래프가 있다면 연결성분은 2개의 연결 성분이 있는것
//특징 - 연결 성분에 속한 모든 정점을 연결하는 경로가 있어야하고
//또 다른 연결성분에 속한 정점과 연결하는 경로가 있으면 안되며
//BFS, DFS탐색을 이용해 찾는다.
void Graph_List_Default_Connected_Component(Graph_List_Default_Graph* graph, int visited[]) {
	int i;
	int count = 0;
	//DFS로 정점의 연결성분의 개수를 파악함 A-B-C, D-E의 부분영역 그래프가 있을경우 
	//A-B-C를 연결성분1, D-E를 연결성분2라고 하여 그래프의 어떤 영역들이 연결되어있는지 확인할 수 있음
	for (i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {	//방문하지 않는 정점이 있을경우
			count++;
			Graph_List_Default_DFS(graph, i, visited);
		}
	}
}

//신장트리 - 그래프내 모든 정점을 포함하는 트리로 트리의 특수한 형태로 모든 정점들이 연결되어야 하며 싸이클을 이루면 안된다.
//기존 그래프 -> 신장 트리로 싸이클없이 모든 정점에 간선을 연결시키는 트리구조로 만드는것
//활용 - 전화망이든 네트워크든 비용에따라 특정 목적지에 도착하기 위해 최소 비용 경로를 구현하는 구조를 따로 만들어서 진행할때 사용
void Graph_List_Default_DFS_SpanningTree(Graph_List_Default_Graph* graph ,int vertex, int visited[]) {
	//DFS를 이용한 신장트리 경로 구현
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
					//BFS를 이용한 방법도 있다.
				}
				temp = temp->next;
			}
			printf("\n");
		}
	}
}

//그래프 출력
void Graph_List_Default_printGraph(Graph_List_Default_Graph* graph) {
	for (int v = 0; v < graph->numVertices; v++) {
		Graph_List_Default_Vertex* temp = graph->adjLists[v];
		printf("\n 정점 %d: ", v);
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


//인접행렬을 이용한 기본 그래프(무방향그래프)

#define MAX_VERTICES 10  //그래프의 최대 정점 개수

typedef struct Graph_Arr_Default_Graph {
	int numVertices;
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
}Graph_Arr_Default_Graph;

//그래프 초기화
void Graph_Arr_Default_initGraph(Graph_Arr_Default_Graph* graph, int vertices) {
	if (vertices > MAX_VERTICES) {
		printf("정점의 개수가 너무 많습니다.");
		return;
	}
	graph->numVertices = vertices;	
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			graph->adjMatrix[i][j] = 0; //간선이 존재하지 않으니 초기값 0
		}
	}
}

//그래프의 탐색 너비우선탐색(BFS)
//인접행렬시 BFS의 시간 복잡도는 O(V^2)
void Graph_Arr_Default_BFS(Graph_Arr_Default_Graph* graph, int startVertex) {
	//시작 정점의 값을 기준으로 너비를 탐색하면서 그래프를 탐색해나가는 방식이다.
	boolean visited[MAX_VERTICES] = { 0 };//false로 채움
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFS 탐색 순서: ");
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

//깊이 우선 탐색(DFS)
//인접리스트시 DFS의 시간복잡도는 O(V^2)
//간선의 크기는 시간복잡도에 영향을 주지않기에 밀집그래프(정점<간선)에 적합
void Graph_Arr_Default_DFS(Graph_Arr_Default_Graph* graph, int vertex, boolean visited[]) {
	visited[vertex] = 1;
	printf("%d ", vertex);

	for (int i = 0; i < graph->numVertices; i++) {
		if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
			Graph_Arr_Default_DFS(graph, i, visited);
		}
	}
}

//간선 추가
void Graph_Arr_Default_addEdge(Graph_Arr_Default_Graph* graph, int start, int end) {
	graph->adjMatrix[start][end] = 1;
	graph->adjMatrix[end][start] = 1;	//무방향이니 반대방향도 설정해줌
}

//인접행렬에서 간선 삭제 삭제하고자 하는 정점간의 간선을 지움
void Graph_Arr_Default_Delete_Edge(Graph_Arr_Default_Graph* graph, int start, int end) {
	graph->adjMatrix[start][end] = 0;
	graph->adjMatrix[end][start] = 0;
}

//인접행렬에서 정점 삭제
void Graph_Arr_Default_Delete_Vertex(Graph_Arr_Default_Graph* graph, int vertex) {
	//해당 정점과 연결된 간선을 모두 삭제해야함 간선 삭제가 바탕이 되어야 함
	for (int i = 0; i < graph->numVertices; i++) {
		graph->adjMatrix[vertex][i] = 0;
		graph->adjMatrix[i][vertex] = 0;
	}
	//이것도 완전한 정점의 삭제라고 보기는 어려움
}

//연결성분을 찾기
//연결성분 - 서로 연결되어 있는 여러개의 고립된 부분 그래프 각각을 연결성분이라고 함
//A-B-C , D-E 이런식의 그래프가 있다면 연결성분은 2개의 연결 성분이 있는것
//특징 - 연결 성분에 속한 모든 정점을 연결하는 경로가 있어야하고
//또 다른 연결성분에 속한 정점과 연결하는 경로가 있으면 안되며
//BFS, DFS탐색을 이용해 찾는다.
void Graph_Arr_Default_Connected_Component(Graph_Arr_Default_Graph* graph, int visited[]) {
	int i;
	int count = 0;
	//DFS로 정점의 연결성분의 개수를 파악함 A-B-C, D-E의 부분영역 그래프가 있을경우 
	//A-B-C를 연결성분1, D-E를 연결성분2라고 하여 그래프의 어떤 영역들이 연결되어있는지 확인할 수 있음
	for (i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {	//방문하지 않는 정점이 있을경우
			count++;
			Graph_Arr_Default_DFS(graph, i, visited);
		}
	}
}

//신장트리 - 그래프내 모든 정점을 포함하는 트리로 트리의 특수한 형태로 모든 정점들이 연결되어야 하며 싸이클을 이루면 안된다.
//기존 그래프 -> 신장 트리로 싸이클없이 모든 정점에 간선을 연결시키는 트리구조로 만드는것
//활용 - 전화망이든 네트워크든 비용에따라 특정 목적지에 도착하기 위해 최소 비용 경로를 구현하는 구조를 따로 만들어서 진행할때 사용
void Graph_Arr_Default_DFS_SpanningTree(Graph_Arr_Default_Graph* graph, int vertex, int visited[]) {
	//DFS를 이용한 신장트리 경로 구현
	visited[vertex] = 1;
	printf("%d ", vertex);

	for (int i = 0; i < graph->numVertices; i++) {
		if (!visited[i]) {
			for (int i = 0; i < graph->numVertices; i++) {
				if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
					printf("(%d -> %d)\n", vertex, i);
					Graph_Arr_Default_DFS(graph, vertex, visited);
					//Graph_Arr_Default_BFS(graph, vertex, visited);
					//BFS를 이용한 방법도 있다.
				}
			}
		}
	}
}

//그래프 출력
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


//지금까지의 그래프는 단순 그래프로 그저 정점의 값과 간선이 연결만 되어있는것으로 구현하는 기본 그래프에 지나지 않는다.
//이번에 만들어볼 그래프들은 단순 그래프가 아닌 그래프의 간선별로 비용이 존재해 경로탐색에 신중을 가하는 구조가 존재한다.

//인접리스트의 간선별 비용이 존재하는 그래프 구현
typedef struct Graph_List_Weight_Edge {
	int vertex; //목적지의 정점
	int weight; //이 간선의 가중치 비용
	struct Graph_List_Weight_Edge* next;	//다른 간선을 가리키는 포인터 인접리스트
}Graph_List_Weight_Edge;

typedef struct Graph_List_Weight_Vertex {
	struct Graph_List_Weight_Edge* head; //간선 리스트의 시작
}Graph_List_Weight_Vertex;

typedef struct Graph_List_Weight_Graph {
	int numVertices; //정점의 개수
	struct Graph_List_Weight_Vertex** vertices;		//정점 리스트
}Graph_List_Weight_Graph;

//정점 생성
void Graph_List_Weight_createVertex(Graph_List_Weight_Graph* graph) {
	Graph_List_Weight_Vertex* vertex = (Graph_List_Weight_Vertex*)malloc(sizeof(Graph_List_Weight_Vertex));
	for (int i = 0; i < graph->numVertices; i++) {
		graph->vertices[i] = vertex;
		vertex = (Graph_List_Weight_Vertex*)malloc(sizeof(Graph_List_Weight_Vertex));
	}
}

//그래프 초기화
Graph_List_Weight_Graph* Graph_List_Weight_createGraph(int numVertices) {
	Graph_List_Weight_Graph* graph = (Graph_List_Weight_Graph*)malloc(sizeof(Graph_List_Weight_Graph));
	graph->numVertices = numVertices;

	graph->vertices = (Graph_List_Weight_Vertex*)malloc(sizeof(Graph_List_Weight_Vertex) * numVertices);

	//정점을 생성하고 정점이 가리키는 간선값들을 NULL로 초기화해줌
	Graph_List_Weight_createVertex(graph);
	for (int i = 0; i < numVertices; i++) {
		graph->vertices[i]->head = NULL;
	}

	return graph;
}

//간선 추가 함수(양방향)
void Graph_List_Weight_addEdge(Graph_List_Weight_Graph* graph, int src, int dest, int weight) {
	//src와 dest라는 두개의 정점을 만들고 가중치 weight를 통해서 서로 간선을 연결해주면 된다.
	Graph_List_Weight_Edge* edge = (Graph_List_Weight_Edge*)malloc(sizeof(Graph_List_Weight_Edge));
	edge->vertex = dest;
	edge->weight = weight;
	edge->next = graph->vertices[src]->head;	//간선이 가리키는 정점src의 다음 간선리스트를 가짐
	graph->vertices[src]->head = edge;		//기존 정점리스트를 갱신

	edge = (Graph_List_Weight_Edge*)malloc(sizeof(Graph_List_Weight_Edge));
	edge->vertex = src;
	edge->weight = weight;
	edge->next = graph->vertices[dest]->head;	//간선이 가리키는 정점 dest의 다음 간선 리스트를 가짐
	graph->vertices[dest]->head = edge;		//기존 정점리스트를 갱신
}

//그래프의 탐색 너비우선탐색(BFS)
//인접리스트시 BFS의 시간 복잡도는 O(V+E)
//이렇듯 정점과 더불어 간선의 크기가 늘어날수록 오래걸리기에 희소그래프(간선<정점)에 훨씬 효율적
void Graph_List_Weight_BFS(Graph_List_Weight_Graph* graph, int startVertex) {
	boolean* visited = (boolean*)malloc(sizeof(boolean) * graph->numVertices);
	for (int i = 0; i < graph->numVertices; i++) visited[i] = 0;

	int* queue = (int*)malloc(sizeof(int) * graph->numVertices);
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFS탐색 순서 : ");
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

//깊이 우선 탐색(DFS)
//인접리스트시 DFS의 시간복잡도는 O(V+E)
//이렇듯 정점과 더불어 간선의 크기가 늘어날수록 오래걸리기에 희소그래프(간선<정점)에 훨씬 효율적
//재귀를 이용해서 탐색함 배열 visited에 vertex값을 넣기에 재귀를 이용해도 문제없음
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

//그래프 출력 함수
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

//인접행렬에 비용이 추가된 그래프
typedef struct Graph_Arr_Weight_Graph {
	int numVertices;
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
}Graph_Arr_Weight_Graph;

//그래프 초기화
void Graph_Arr_Weight_initGraph(Graph_Arr_Weight_Graph* graph, int vertices) {
	if (vertices > MAX_VERTICES) {
		printf("정점의 개수가 너무 많습니다.");
		return;
	}
	graph->numVertices = vertices;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			graph->adjMatrix[i][j] = 0; //간선이 존재하지 않으니 초기값 0
		}
	}
}

//간선 추가
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

//그래프의 탐색 너비우선탐색(BFS)
//인접행렬시 BFS의 시간 복잡도는 O(V^2)
void Graph_Arr_Weight_BFS(Graph_Arr_Weight_Graph* graph, int startVertex) {
	//시작 정점의 값을 기준으로 너비를 탐색하면서 그래프를 탐색해나가는 방식이다.
	boolean visited[MAX_VERTICES] = { 0 };//false로 채움
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	visited[startVertex] = 1;
	queue[rear++] = startVertex;

	printf("BFS 탐색 순서: ");
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

//깊이 우선 탐색(DFS)
//인접리스트시 DFS의 시간복잡도는 O(V^2)
//간선의 크기는 시간복잡도에 영향을 주지않기에 밀집그래프(정점<간선)에 적합
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

//최소비용신장트리
//최단경로
//위상정렬 
//이 3가지는 나중에 알고리즘 공부할때 진행