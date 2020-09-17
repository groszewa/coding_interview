
#include <vector>
#include <stdlib.h>
#include <stdio.h>

class Bag {
private:
  int beans;
  std::vector<Bag> bagList;
public:
  Bag(Bag newBag, int newBeans) {
    this->beans = newBeans;
    this->bagList.push_back(newBag);
  }
  Bag(int newBeans) {
    this->beans = newBeans;
  }
  void addBag(Bag newBag) {
    this->bagList.push_back(newBag);
  }
  bool isLeafBag() {
    return this->bagList.empty();
  }
  
  int getBeans() {
    if(this->isLeafBag()) return this->beans;
    int beanCount = 0;
    for(auto bag : this->bagList) {
      beanCount += bag.getBeans();
    }
    return this->beans + beanCount;
  }
};



int main() {
  Bag bag1(12);
  Bag bag2(bag1,4);
  bag2.addBag(Bag(Bag(3),6));
  Bag bag3(Bag(1),2);
  bag3.addBag(Bag(1));
  Bag bagTop(bag2,7);
  bagTop.addBag(bag3);
  bagTop.addBag(Bag(3));
  bagTop.addBag(Bag(5));

  printf("Total beans in bagTop is %d\n",bagTop.getBeans());
  printf("Total beans in bag1 is %d\n",bag1.getBeans());
  printf("Total beans in bag2 is %d\n",bag2.getBeans());
  printf("Total beans in bag3 is %d\n",bag3.getBeans());
  
  return 0;
}
