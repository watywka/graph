#include "graph.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    opterr = 0;
    int fflag = 0, oflag = 0;
    int n = 20;
    int p = 5;
    int* a;
    int opt;
    ifstream fin;
    ofstream fout;
    if(argc == 1)
    {
        cout << "Usage:\n";
        return 1;
    }
    while((opt = getopt(argc,argv,"n:p:o:f:")) != -1)
    {
        switch(opt) {
            case 'p':
                if(sscanf(optarg,"%d",&p) != 1)
                {
                    cout << "Can't read max path value\n";
                    return -1;
                }
                if ( p < 1)
                {
                    cout << "Negative max path value \n";
                    return -1;
                }
                break;
            case 'n':
                if(sscanf(optarg,"%d",&n) != 1)
                {
                    cout << "Can't read graph size value\n";
                    return -1;
                }
                if (n < 1)
                {
                    cout << "Negative graph size value \n";
                    return -1;
                }
                break;
            case 'o':
                if(fflag == 1)
                {
                    cout << "Can't use -f an -o simultaneously\n";
                    fin.close();
                }
                if(oflag == 1)
                {
                    cout << "Multiple usage of -o option is not allowed\n";
                    fout.close();
                    return -1;
                }
                oflag = 1;
                fout.open(optarg, ofstream::out);

                if(!fout.is_open())
                {
                    cout << "Can't open\n";
                    return -1;
                }
                break;
            case 'f':
                if(oflag == 1)
                {
                    cout << "Can't use -f an -o simultaneously\n";
                    fout.close();
                }
                if(fflag == 1)
                {
                    cout << "Multiple usage of -f option is not allowed\n";
                    fin.close();
                    return -1;
                }
                fflag = 1;

                fin.open(optarg, ifstream::in);

                if(!fin.is_open())
                {
                    cout << "Can't open\n";
                    return -1;
                }
                break;
            case '?':
                if((optopt == 'p') || (optopt == 'f') || (optopt == 'o')) {
                    cout << "An argument is required\n";
                    return -1;
                }

                cout << "Unknow option\n";
                return -1;
                break;
            default:
                return -1;
        }
    }
    if(optind<argc)
    {
        cout << "Wrong options format\n";
        if(fflag) fin.close();
        return -1;
    }
    if(fflag)
    {
        if(!(fin >> n))
        {
            cout << "Corrupted file\n";
            fin.close();
            return -1;
        }
        if(n<1)
        {
            cout << "Wrong matrix size\n";
            fin.close();
            return -1;
        }
        if(!(a=(int*) malloc(sizeof(int)*n*n)))
        {
            if(a) free(a);
            cout << "Can't allocate memory\n";
            fin.close();
            return -1;
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(!(fin >> a[i*n+j]))
                {
                    cout << "Corrupted file\n";
                    fin.close();
                    free(a);
                    return -1;
                }
            }
        }
        fin.close();
        vector<int>* ans = new vector<int>();
        search(n,a, ans);
        if (ans->size() == 0)
        {
            cout << "Циклов не найдено" << endl;
        }
        else
        {
            cout <<"Максимальный цикл имеет длину " << ans->size() << "\n";
            for(auto p : *ans)
            {
                cout << p << " ";
            }
            cout << endl;
        }
        delete ans;
        free (a);
    }

    if(oflag)
    {
        a = new int[n*n];
        gen(n, p, a);
        fout << n << endl;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                fout << a[n*i+j] << " ";
            }
            fout << endl;
        }
        fout.close();
        delete[] a;

    }

}

