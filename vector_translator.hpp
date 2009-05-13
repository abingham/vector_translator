#include <vector>

#include <boost/foreach.hpp>
#include <boost/python/def.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/list.hpp>
#include <boost/python/module.hpp>
#include <boost/python/to_python_converter.hpp>

namespace c3db {

	template <typename T>
	struct vector_to_python_list
	{
			static PyObject* convert(std::vector<T> const& v)
				{
					using namespace boost::python;

					list l;
					BOOST_FOREACH(const T& val, v)
					{
						l.append(val);
					}

					return boost::python::incref(l.ptr());
				}
	};

	template <typename T>
	struct vector_from_python_list
	{
			vector_from_python_list()
				{
					boost::python::converter::registry::push_back(
						&convertible,
						&construct,
						boost::python::type_id< std::vector<T> >());
				}

			static void* convertible(PyObject* obj_ptr)
				{
					if (!PyList_Check(obj_ptr)) return 0;
					return obj_ptr;
				}

			static void construct(
				PyObject* obj_ptr,
				boost::python::converter::rvalue_from_python_stage1_data* data)
				{
					using namespace boost::python;

					extract<list> x(obj_ptr);
					if (!x.check())
						throw_error_already_set();
					
					list l = x();
					
					void* storage = (
						(converter::rvalue_from_python_storage< std::vector<T> >*)
						data)->storage.bytes;
					new (storage) std::vector<T>();
					
					std::vector<T>& v = *reinterpret_cast< std::vector<T>* >(storage);

					for (int idx = 0; idx < len(l); ++idx)
					{
						extract<T> ext(l[idx]);
						if (!ext.check())
						{
							v.std::vector<T>::~vector<T>();
							throw_error_already_set();
						}

						v.push_back(ext());
					}

					data->convertible = storage;
				}
	};

	template <typename T>
	void init_module()
	{
		boost::python::to_python_converter<
		    std::vector<T>,
			vector_to_python_list<T> >();
	
	vector_from_python_list<T>();
	}

}

BOOST_PYTHON_MODULE(c3db_vector)
{
	c3db::init_module<int>();
}
