#include <string>
#include <iostream>

/*
@static 公共接口，所有函数都可以调用，返回需要的值
    1.1 所有节点都可以进行调用
    1.2 所有的函数都可以随时应用

@知识点
    1. namespace/enum
    2. 单例模式
    3. 构造函数里初始化

    枚举， 默认从0开始，也可以自己定义
    typedef enum XXType 
    {
        AM = 1,
        B
    }  XXTYPE;
    命名空间，起到限制作用域的效果，防止与同命名冲突
    namesapce YY
    {
        class XXManager 
        {

        };
    }
*/

typedef enum XXType 
{
    A = 1,
    B
} XXTYPE;

namespace project_XX 
{
    class XXManager 
    {
        public:
            // 最简单的单例实现
            static XXManager* getInstance()
            {
                return instance_;
            }
            // 函数末尾加了const，不能改变成员变量值，一般getXXX函数都加const
            std::string getXX(const XXTYPE& type, int idx) const;
        
        private:
            // 禁止构造
            /*
            1. delete
            2. private
            3. virtual
            */
           XXManager(const XXManager&) = delete;
           XXManager& operator = (const XXManager&) = delete;

           bool init();

           XXManager() : is_init_(false) 
           {
                // 构造函数里调用初始化，也可以单独调用
                is_init_ = init();
           }

           bool is_init_;

           // 静态成员变量，初始化只能在外部
           static XXManager* instance_;
    };
}

namespace project_XX 
{
    // 类外初始化静态成员变量，new动态分配内存空间，std::nothrow避免内存分配失败引起异常
    // std::bad_alloc
    XXManager* XXManager::instance_ = new(std::nothrow) XXManager;

    std::string XXManager::getXX(const XXTYPE& type, int idx) const 
    {
        if(!is_init_) 
        {
            return " ";
        }

        /*
        @ TODO
            主要逻辑自己实现
            初始化的一些配置在这里实现或者加载
        */
        std::cout << "is_init_: " << is_init_ << std::endl;
        return "XX";
    }

    bool XXManager::init() 
    {
        /*
        @ TODO
        1. 读取配置文件
        2. 所有变量的一个初始化
        3. 任何实现自己补充
        */
       return true;
    }
}

/*
@ 为什么要设计成static函数?
    1. 编译时分配内存，存储在静态存储区
    2. 只能被当前文件中其它函数调用，避免与同名的其它函数产生冲突
    3. 生命周期从程序开始到结束

    内存分配，生命周期，隐蔽性
*/

static std::string getXX_entry(const XXType& type, int idx = -1) 
{
    // 调用单例管理的入口
    std::cout << "common entry, I am coming" << std::endl;
    return project_XX::XXManager::getInstance()->getXX(type, idx);
}

// 举例说明
class AA 
{
public:
    bool process() 
    {
        // 对外开放公共接口的调用
        std::string aa = getXX_entry(A, 10);
        /*
        @ TODO
            处理逻辑根据自己工程实现
            1. 
            2. 
            3.
        */
       return true;
    }
};

class BB 
{
public:
    bool process() 
    {
        std::string bb = getXX_entry(B, 10);
        /*
        @ TODO
        处理逻辑根据自己工程实现
        */
       return true;
    }
};

int main() 
{
    AA aa;
    aa.process();

    return 0;
}