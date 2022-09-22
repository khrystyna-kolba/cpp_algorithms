#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<fstream>
using namespace std;

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data_;
        Node* next_;
        Node(T new_data, Node* new_next = nullptr) {
            data_ = new_data;
            next_ = new_next;
        }
        ~Node() {
            delete next_;
        }
    };
    unsigned int size_;
    Node* head_;
    Node* tail_;
    Node* current_;

public:
    LinkedList() {
        current_ =head_=tail_= nullptr;
        size_ = 0;
    }
    ~LinkedList() {
        delete head_;
    }
    void push(T new_element) {
        Node* new_node = new Node(new_element, nullptr);
        if (!(tail_ == nullptr)) {
            tail_->next_ = new_node;
            if (size_ == 1) {
                current_=head_=tail_;
            }
            tail_ = new_node;
        }
        else {
            current_ = head_ = tail_=new_node;
        }

        size_++;
    }
    T get_data() {
        return current_->data_;
    }
    void go_to_head() {
        current_ = head_;
    }
    void go_to_next() {
        if (!current_is_a_tail()) {
            current_ = current_->next_;
        }
    }
    bool current_is_a_tail() {
        return current_ == tail_;
    }
    bool current_is_a_head() {
        return current_ == head_;
    }
    bool is_empty() {
        return size_ == 0;
    }
    unsigned int getSize() {
        return size_;
    }
};

class Node {
public:
    char name;
    char parent='0';
    //Node* parent=nullptr;
    double path_from_initial=0;
    Node() {}
    ~Node() {
        //delete parent;
    }
    void input(istream& is) {
        is >> name;
    }
};
struct WeightedNode {
    double weight=0;
    char node;
};
class WeightedGraph {
public:
    size_t num_of_vertices;
    LinkedList<WeightedNode>* vertices;
    WeightedGraph() {
        vertices = nullptr;
    }
    void show(ostream& os) {
        for (int i = 0; i < num_of_vertices; i++) {
            os<<vertices[i].get_data().node;
            if(!(vertices[i].current_is_a_tail()))vertices[i].go_to_next();
            else {
                continue;
            }
            os << " : ";
            while (!vertices[i].current_is_a_tail()) {
                os << vertices[i].get_data().node;
                os << " weight = " << vertices[i].get_data().weight;
                vertices[i].go_to_next();
                os << " , ";
            }
            os << vertices[i].get_data().node;
            os << " weight = " << vertices[i].get_data().weight;
            os << endl;
            vertices[i].go_to_head();
        }
    }
    void input(istream& is) {
        cout << "input num of vertices: " << endl;
        is >> num_of_vertices;
        vertices = new LinkedList<WeightedNode>[num_of_vertices];
        cout << "input all vertices: (for example a,b,c,d,....)" << endl;
        for (int i = 0; i < num_of_vertices; i++) {
            WeightedNode x;
            is >> x.node;
            //x.node.input(is);
            vertices[i].push(x);
        }
        cout << "now we are going to add all edges" << endl;
        cout << "please enter the num of terminal vertices of the vertices in order you entered above" << endl;
        cout << "then weight of the edge from initial" << endl;
        cout << "repeat" << endl;
        for (int i = 0; i < num_of_vertices; i++) {
            size_t num_of_terminal;
            is >> num_of_terminal;
            for (size_t j = 0; j < num_of_terminal; j++) {
                char n;
                double weight;
                is >> n >> weight;
                WeightedNode to_add;
                to_add.node=n;
                to_add.weight = weight;
                vertices[i].push(to_add);
            }
        }
    }
};
double path_from_vector(vector<Node> x, char y) {
    for (auto p : x) {
        if (p.name == y) {
            return p.path_from_initial;
        }
    }
    return 0;
}
int find_index_in_vector(vector<Node> x, char y) {
    int count = -1;
    for (auto p : x) {
        count++;
        if (p.name == y) {
            return count;
        }
    }
    return 0;
}
bool node_name_is_in_vector(vector<Node> x, char y) {
    for (auto p : x) {
        if (p.name == y) {
            return true;
        }
    }
    return false;
}
vector<Node> dijsktra(WeightedGraph x, char initial, char terminal) {
    vector<Node> explored_set;
    vector<Node> frontier;
    Node temp;
    Node temp_parent;
    int s_index;
    //starting with initial vertice
    for (int i = 0; i < x.num_of_vertices; i++) {
        if (x.vertices[i].get_data().node == initial&& !x.vertices[i].current_is_a_tail()) {
            s_index = i;
            temp.name = x.vertices[i].get_data().node;
            explored_set.push_back(temp);
            temp_parent = temp;
            x.vertices[i].go_to_next();
            break;
        }
    }

    do {
        //finding all terminal vertices from vertice with the minimal known path
        while (!x.vertices[s_index].current_is_a_tail()) {
            temp.name = x.vertices[s_index].get_data().node;
            temp.parent = temp_parent.name;
            temp.path_from_initial += x.vertices[s_index].get_data().weight;
            if (node_name_is_in_vector(frontier, temp.name)) {
                if (path_from_vector(frontier, temp.name) > temp.path_from_initial) {

                    frontier[find_index_in_vector(frontier, temp.name)] = temp;
                }
            }
            else {
                frontier.push_back(temp);
            }
            x.vertices[s_index].go_to_next();
            temp = temp_parent;
        }
        temp.name = x.vertices[s_index].get_data().node;
        temp.parent = temp_parent.name;
        temp.path_from_initial += x.vertices[s_index].get_data().weight;
        if (node_name_is_in_vector(frontier, temp.name)) {
            if (path_from_vector(frontier, temp.name) > temp.path_from_initial) {

                frontier[find_index_in_vector(frontier, temp.name)] = temp;
            }
        }
        else {
            frontier.push_back(temp);
        }
        x.vertices[s_index].go_to_head();
        temp = temp_parent;
        temp.path_from_initial = 0;
        //finding the vertex with min path
        for (auto front = frontier.begin(); front != frontier.end();) {
            if (temp.path_from_initial > (*front).path_from_initial|| temp.path_from_initial == 0) {
                if (node_name_is_in_vector(explored_set, (*front).name)) {
                    if (frontier.size() == 1) {
                        front = frontier.erase(front);
                        continue;
                    }
                    front = frontier.erase(front);
                    continue;
                }
                temp = *front;
            }
            front++;
        }
        for (int i = 0; i < x.num_of_vertices; i++) {
            if (x.vertices[i].get_data().node == temp.name) {
                s_index = i;
                explored_set.push_back(temp);
                x.vertices[i].go_to_next();
                temp_parent = temp;
                break;
            }
        }
        

    } while (frontier.size()!=0);
    explored_set.pop_back();
    return explored_set;
}


int main() {
   
    ifstream fin("Text.txt");//читання з файлу
    WeightedGraph x;
    x.input(fin);
    x.show(cout);
    for (auto y : dijsktra(x, 'a', 'c')) {
        cout << y.name <<" "<<y.parent<<" "<<y.path_from_initial<< endl;
    }
    fin.close();


}