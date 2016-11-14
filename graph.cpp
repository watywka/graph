#include "graph.h"

graph::graph()
{
}

graph::graph(int n, int* mat)
{
    this->n = n;
    matrix = (int*)malloc(sizeof(int)*n*n);
    for (int i=0;i< n*n;i++)
    {
        matrix[i]=mat[i];
    }
}

graph::~graph()
{
    free(matrix);
}

int graph::get_n()
{
    return n;
}

void graph::get_next(int k,set<int>* visited, set<int>* out)
{
    out->clear();
    for(int i=0;i<n;i++)
    {
        if((matrix[k*n+i] == 1) && (visited->find(i) == visited->end()))
            out->insert(i);
    }
}


int graph::path(int start, int cur, set<int>*  visited, vector<int>* out)
{
    set<int>* next = new set<int>();
    set<int>* tmp = new set<int>(*visited);
    get_next(cur, visited, next);
    int val, max = -1;
    int max_n;
    vector<int>*  cur_path = new vector<int>();
    vector<int>* max_path = new vector<int>();
    for(auto r: *next)
    {
        cur_path->push_back(r);
        if(r ==  start)
        {
            val = 0;
        }
        else
        {
            tmp->insert(r);
            val = path(start, r, tmp, cur_path);
            tmp->erase(r);
        }
        if (val>max)
        {
            max = val + 1;
            *max_path = *cur_path;
        }
        cur_path->clear();
    }
    out->insert(out->end(),max_path->begin(),max_path->end());
    delete cur_path;
    delete max_path;
    delete next;
    delete tmp;
    return max;
}

void search (int n, int* a, vector<int>* out)
{
    graph* A = new graph(n,a);
    int max = -1;
    int val;
    set<int>* t = new set<int>();
    vector<int>*  max_path = new vector<int>();
    vector<int>*  tmp_path = new vector<int>();
    for(int i=0; i< A->get_n();i++)
    {
        tmp_path->clear();
        val = A->path(i,i,t, tmp_path); 
        if(val>max)
        {
            max = val;
            *max_path = *tmp_path;
        }
    }
    *out = *max_path;
    delete t;
    delete tmp_path;
    delete max_path;
    delete A;
}

void shuf(int n, int* a)
{
    vector<int>* shuf = new vector<int>();
    for(int i = 0;i < n; i++)
    {
        shuf->push_back(i);
    }
    srand(time(0));
    random_shuffle(shuf->begin(), shuf->end());
    int* b = new int[n*n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            b[i*n+j] = a[(*shuf)[i]*n+(*shuf)[j]];
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            a[i*n+j] = b[i*n+j];
        }
    }
    delete b;
}
void gen(int n, int p, int* a)
{
    srand(time(0));
    vector<int>* razb = new vector<int>();
    int left = n - p;
    razb->push_back(p);
    while ( left > 0)
    {
        int ad = min(rand() % p + 1, left);
        razb->push_back(ad);
        left -= ad;
    }
    int i = 0;
    for (int j=0;j<n*n;j++)
    {
        a[j]=0;
    }
    for (auto tot: *razb)
    {
        cout << tot << " ";
        for (int j=0;j<tot-1;j++)
        {
            a[(j+i)*n+j+i+1] = 1;
        }
        a[(tot+i-1)*n + i] = 1;
        i+=tot;
    }
    cout << endl;
    int svyaz = razb->size();
    int* DAG = new int[(svyaz)*(svyaz)];
    for(int j = 0; j < svyaz; j++)
    {
        for (int k = 0; k< svyaz; k++)
        {
            if(j>k) DAG[j*svyaz+k] = rand() % 1;
            else DAG[j*svyaz+k] = 0;
        }
    }
    shuf(svyaz,DAG);
    int v_off;
    int h_off;
    for(int j = 0; j < svyaz; j++)
    {
        for (int k = 0; k< svyaz; k++)
        {
            v_off = 0;
            h_off = 0;
            if(DAG[j*svyaz+k] == 1)
            {
                for(int l=0;l<j;l++)
                {
                    v_off+=(*razb)[l];
                }
                for(int l=0;l<k;l++)
                {
                    h_off+=(*razb)[l];
                }
            }
            int v_rnd = rand() % (*razb)[j];
            int h_rnd = rand() % (*razb)[k];
            a[(v_off+v_rnd)*n+(h_off+h_rnd)] = 1;
        }
    }

    shuf(n,a);


}
