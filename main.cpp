#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <boost/python.hpp>

#include <vector_translator.hpp>

using namespace boost::python;
using namespace std;

int main(int argc, char** argv)
{
		Py_Initialize();

		c3db::init_module<int>();

		try {
				vector<int> v;
				v.push_back(1);
				v.push_back(2);
				v.push_back(3);
				
				object obj = import("test").attr("Foo")();
				obj.attr("x") = v;
				// import("test").attr("foo")(obj);

				v = extract< vector<int> >(obj.attr("x"));
				cout << v.size() << endl;
				copy(v.begin(),
						 v.end(),
						 ostream_iterator<int>(cout, ", "));
		} catch (const error_already_set&) {
				PyErr_Print();
		}

		return 0;
}
