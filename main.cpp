#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

class Tensor {
    private:
    	int rows,cols,shape;
        vector<float> data;
        inline float f(float x) {
        	return 1/(1+exp(-x));
        }
        inline void print1d() {
        	assert(data.empty()!=true);
        	cout<<"Tensor : ({ ";
        	for(int i=0;i<size()-1;i++) {
        		cout<<data[i]<<" ,";
        	}
        	cout<<data[size()-1];
        	cout<<" })"<<endl;
        }
		inline void print2d() {
			assert(data.empty()!=true);
		    cout << "Tensor : ({\n";
		    for (int r=0;r<rows;r++){
		        cout << "  { ";
		        for(int c=0;c<cols;c++){
		            cout << data[r*cols + c];
		            if(c != cols-1) cout << ", ";
		        }
		        cout << " }\n";
		    }
		    cout << "})" << endl;
		}
    public:
    
    	// Tensor Constructors
    	
    	Tensor(vector<float> arr) {
    		data = arr;
    		shape=1;rows=1;cols=arr.size();
    	}
    	Tensor(int size, float fill=0.0) {
    	    rows=1;shape=1;cols=size;
    		data.resize(size,fill);
    	}
		Tensor(const vector<vector<float>>& arr2D) {
		    rows = arr2D.size();
		    cols = arr2D.empty() ? 0 : arr2D[0].size();
		    shape = 2;
		    data.clear();
		    for (const auto& row : arr2D) {
		        if (row.size() != cols)
		            throw runtime_error("All rows must have the same length");
		        data.insert(data.end(), row.begin(), row.end());
		    }
		}
    	Tensor(int row,int col, float fill=0.0) {
    		rows=row; cols=col;shape=2;
			data.resize(row*col,fill);
    	}
    	Tensor() {data.resize(0,0.0f);shape=1;rows=0;cols=0;}
    	
    	// Helper Functions
    	
        int size() { return data.size(); }
        void print() {
			if (shape==1) {print1d();}
			else if (shape==2) {print2d();}
        }
        
        // Math functions
        
        void sigmoid_() {
            for (int i=0;i<size();i++) {
        		data[i] = f(data[i]);
			}
        }
        Tensor sigmoid() {
        	Tensor out(*this);
            for (int i=0;i<size();i++) {
        		out.data[i] = f(data[i]);
			}
			return out;
        }
        
        void power_(float x) {
        	for (int i=0;i<size();i++) {
        		data[i] = pow(data[i],x);
        	}
        }
        Tensor power(float x) {
    		Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = pow(data[i],x);
        	}
        	return out;
        }
        
        float dot(Tensor& t1) {
        	float sum = 0.0f;
        	for (int i=0;i<size();i++) {
        		sum += (data[i] * t1.data[i]);
        	}
        	return sum;
        }
        
        // Easy indexing
        
        float &operator()(int r, int c) { return data[r*cols+c]; }
        const float &operator()(int r,int c) const { return data[r*cols+c]; }
        
        float &operator()(int c) { return data[c]; }
        const float &operator()(int c) const { return data[c]; }
        
        // Operators
        
        Tensor operator+(const Tensor& t) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] + t.data[i];
        	}
        	return out;
		}
		Tensor operator+(float x) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] + x;
        	}
        	return out;
		}
		
        Tensor operator-(const Tensor& t) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] - t.data[i];
        	}
        	return out;
		}
		Tensor operator-(float x) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] - x;
        	}
        	return out;
		}
        Tensor operator*(const Tensor& t) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] * t.data[i];
        	}
        	return out;
		}
		Tensor operator*(float x) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] * x;
        	}
        	return out;
		}
        Tensor operator/(const Tensor& t) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] / t.data[i];
        	}
        	return out;
		}
		Tensor operator/(float x) {
        	Tensor out(*this);
        	for (int i=0;i<size();i++) {
        		out.data[i] = data[i] / x;
        	}
        	return out;
		}
	
		// Inplace operators
		
		void operator+=(const Tensor& t) {
			for (int i=0;i<size();i++) {
				data[i] += t.data[i];
			}
		}
		void operator+=(float x) {
			for (int i=0;i<size();i++) {
				data[i] += x;
			}
		}
		void operator-=(const Tensor& t) {
			for (int i=0;i<size();i++) {
				data[i] -= t.data[i];
			}
		}
		void operator-=(float x) {
			for (int i=0;i<size();i++) {
				data[i] -= x;
			}
		}
		void operator*=(const Tensor& t) {
			for (int i=0;i<size();i++) {
				data[i] *= t.data[i];
			}
		}
		void operator*=(float x) {
			for (int i=0;i<size();i++) {
				data[i] *= x;
			}
		}
		void operator/=(const Tensor& t) {
			for (int i=0;i<size();i++) {
				data[i] /= t.data[i];
			}
		}
		void operator/=(float x) {
			for (int i=0;i<size();i++) {
				data[i] /= x;
			}
		}
};

int main(void) {
	Tensor t(5,1.0f),t2(5,2.0f), t3;
	return 0;
}
