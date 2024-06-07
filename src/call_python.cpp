#include<pybind11/embed.h>
#include<iostream>

namespace py=pybind11;

int main(void) {
    py::scoped_interpreter python;
    py::print("\n \nprompt = hello c++ call python success");

    /*
	import sys
	print sys.path
	print "Hello,World!"
	*/
    py::module sys=py::module::import("sys");
    py::print(sys.attr("path"));
    py::print("Hello, World!"); // use the Python API

    // 更改回原有的编码格式为c++,而非python使用,防止windows平台下cout输出乱码
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::string prompt = "hello, 这是一个测试: en_US.UTF-8";   
    std::cout << "prompt = " << prompt << std::endl;

    /*
	import call_calc
	n = call_calc.add_python(1,2)
	*/
    auto module = py::module::import("call_calc");

    //调用函数时要用attr()进行类型转换
    py::object pya = py::int_(23);;
    py::object pyb = py::int_(46);;
    py::object pyresult = module.attr("add_python")(pya, pyb);

    //python change to c++
    int a = pya.cast<int>();
    int b = py::cast<int>(pyb);
    int result = pyresult.cast<int>();

    //打印结果
    std::cout << "Result from obj.add_python(23,46): " << a << " + " << b << " = " << result << std::endl;

    /*
	from call_calc import MyMath
	obj = MyMath("v0")
	obj.my_add(1,2)
	*/
	py::object MyMath = py::module::import("call_calc").attr("MyMath"); // class
	py::object obj = MyMath("v0"); // class object
	py::object my_add = obj.attr("my_add");// object method
	py::object result2 = my_add(1, 2); // result
	int n2 = result2.cast<int>(); // cast from python type to c++ type
	assert(n2 == 3);
	std::cout << "Result from obj.my_add(1,2) = " << n2 << std::endl;

	/*
	from call_calc import MyMath
	obj = MyMath("v0")
	obj.my_strcon("abc","123");
	*/
	py::object my_strcon = obj.attr("my_strcon"); // object method
	py::object result3 = my_strcon("abc", "123");
	std::string str3 = result3.cast<std::string>();
	std::cout << "Result from obj.my_strcon(abc,123) = " << str3 << std::endl;

    return 0;
}