#include<iostream>

// using namespace std;


namespace hty{

class ref_count{
public:
    ref_count():m_count(1){}

    //加1和减1
    void increase(){
        m_count++;
    }
    long decrease(){
        return --m_count;
    }
    //获取m_count
    long get_count(){
        return m_count;
    }
    // ~ref_count(){}
private:
    long m_count;
};

template<class T>
class shared_ptr{
public:
    //构造函数
    shared_ptr(T* ptr = nullptr):m_ptr(ptr){
        if(ptr){
            m_ref_count = new ref_count();
        }
    }
    //拷贝构造
    shared_ptr(const shared_ptr& other){
        m_ptr = other.m_ptr;
        if(m_ptr){
            other.m_ref_count->increase();
            m_ref_count = other.m_ref_count;
        }
    }
    //赋值
    shared_ptr& operator = (const shared_ptr& other){
        m_ptr = other.m_ptr;
        if(m_ptr){
            other.m_ref_count->increase();
            m_ref_count = other.m_ref_count;
        }
        return *this;
    }
    //析构
    ~shared_ptr(){
        if(m_ptr && m_ref_count->decrease() == 0){
            delete m_ptr;
            delete m_ref_count;
            m_ptr = nullptr;
            m_ref_count = nullptr;
        }
    }
    //获取引用计数
    long use_count(){
        if(m_ptr)
            return m_ref_count->get_count();
        else
            return 0;
    }
private:
    T* m_ptr;
    ref_count* m_ref_count;
};



}


int main(){

    // hty::shared_ptr<int>p1;
    // hty::shared_ptr<int>p2(new int(9));
    // hty::shared_ptr<int>p3(p2);
    // hty::shared_ptr<int>p4(p1);
    // hty::shared_ptr<int>p5 = p2;
    // std::cout<<p1.use_count()<<std::endl;
    // std::cout<<p2.use_count()<<std::endl;
    // std::cout<<p3.use_count()<<std::endl;
    // std::cout<<p4.use_count()<<std::endl;
    // std::cout<<p5.use_count()<<std::endl;
    hty::shared_ptr<int>p(new int(1));
    hty::shared_ptr<int>p1;
    hty::shared_ptr<int>p2(p1);
    hty::shared_ptr<int>p3 = p1;
    std::cout<<p1.use_count()<<std::endl;
}