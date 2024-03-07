import sys
sys.path.append("./out/lib")

import numpy as np
import example

def main():
    # 创建两个NumPy数组
    a = np.array([1, 2, 3], dtype=np.int32)
    b = np.array([4, 5, 6], dtype=np.int32)

    # 调用C++扩展模块中的add_wrapper函数
    result = example.add(a, b)

    # 打印计算结果
    print("Result:", result)

if __name__ == "__main__":
    main()
