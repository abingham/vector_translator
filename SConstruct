env = Environment()

env.Append(CXXFLAGS=['-O0', '-g'])
env.Append(CPPPATH=['.',
                    '/usr/include/python2.6'])
env.Append(LIBS=['python2.6', 
                 'boost_python'])

env.Program('vector_translator', ['main.cpp'])
