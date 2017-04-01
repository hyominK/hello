#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Num {
public:
   int val;
   int flag;
   Num() {
      flag = 0;
   }
};

class Pair {
public:
   Num* num1;
   Num* num2;
   Pair(Num* num1, Num* num2) {
      this->num1 = num1;
      this->num2 = num2;
   }
};

class MinSum {
private:
   vector<Num> vec_num1;
   vector<Num> vec_num2;
   vector<Pair> vec_pair;
public:
   MinSum() {
      vec_num1 = vector<Num>();
      vec_num2 = vector<Num>();
      vec_pair = vector<Pair>();
   }
   void make_vec();
   void print_vec();
   void make_pair();
   void print_pair();
   
   int min_abs();
};

void MinSum::make_vec() {
   int size1, size2;
   cin >> size1 >> size2;

   vec_num1.resize(size1);
   vec_num2.resize(size2);

   for (int i = 0; i < size1; i++) {
      cin >> vec_num1[i].val;
   }

   for (int i = 0; i < size2; i++) {
      cin >> vec_num2[i].val;
   }
}

void MinSum::print_vec() {
   for (int i = 0; i < vec_num1.size(); i++) {
      cout << vec_num1[i].val << ' ';
   }
   cout << endl;

   for (int i = 0; i < vec_num2.size(); i++) {
      cout << vec_num2[i].val << ' ';
   }
   cout << endl;
}

void MinSum::make_pair() {
   vec_num1[0].flag++;
   vec_num2[0].flag++;
   vec_pair.push_back(Pair(&vec_num1[0], &vec_num2[0]));

   vec_num1[vec_num1.size() - 1].flag++;
   vec_num2[vec_num2.size() - 1].flag++;
   vec_pair.push_back(Pair(&vec_num1[vec_num1.size() - 1], &vec_num2[vec_num2.size() - 1]));

   for (int i = 1; i < vec_num1.size() - 1; i++) {
      vec_num1[i].flag++;

      for (int j = 0; j < vec_num2.size(); j++) {
         if (vec_num1[i].val == vec_num2[j].val) {
            vec_num2[j].flag++;
            vec_pair.push_back(Pair(&vec_num1[i], &vec_num2[j]));
            break;
         }


         else if (vec_num1[i].val < vec_num2[j].val) {

            if (j == 0) {
               vec_num2[j].flag++;
               vec_pair.push_back(Pair(&vec_num1[i], &vec_num2[j]));
            }


            else {
               int sub1 = vec_num1[i].val - vec_num2[j - 1].val;
               int sub2 = vec_num2[j].val - vec_num1[i].val;

               if (sub1 <= sub2) {
                  vec_num2[j - 1].flag++;
                  vec_pair.push_back(Pair(&vec_num1[i], &vec_num2[j - 1]));
               }

               else {
                  vec_num2[j].flag++;
                  vec_pair.push_back(Pair(&vec_num1[i], &vec_num2[j]));
               }
            }

            break;
         }

         else if (j == vec_num2.size() - 1) {
            vec_num2[j].flag++;
            vec_pair.push_back(Pair(&vec_num1[i], &vec_num2[j]));
         }
      }

   }
   
   for (int i = 1; i < vec_num2.size() - 1; i++) {
      if (vec_num2[i].flag == 0) {
         vec_num2[i].flag++;

         for (int j = 0; j < vec_num1.size(); j++) {
            if (vec_num2[i].val == vec_num1[j].val) {
               vec_num1[j].flag++;
               vec_pair.push_back(Pair(&vec_num2[i], &vec_num1[j]));
               break;
            }

            else if (vec_num2[i].val < vec_num1[j].val) {

               if (j == 0) {
                  vec_num1[j].flag++;
                  vec_pair.push_back(Pair(&vec_num2[i], &vec_num1[j]));
               }


               else {
                  int sub1 = vec_num2[i].val - vec_num1[j - 1].val;
                  int sub2 = vec_num1[j].val - vec_num2[i].val;

                  if (sub1 <= sub2) {
                     vec_num1[j - 1].flag++;
                     vec_pair.push_back(Pair(&vec_num2[i], &vec_num1[j - 1]));
                  }

                  else {
                     vec_num1[j].flag++;
                     vec_pair.push_back(Pair(&vec_num2[i], &vec_num1[j]));
                  }
               }

               break;
            }

            else if (j == vec_num1.size() - 1) {
               vec_num1[j].flag++;
               vec_pair.push_back(Pair(&vec_num2[i], &vec_num1[j]));
            }
         }
      }

   }
}

int MinSum::min_abs() {
   int sum = 0;

   for (int i = 0; i < vec_pair.size(); i++) {
      if (vec_pair[i].num1->flag > 1 && vec_pair[i].num2->flag > 1)
         continue;

      sum += abs(vec_pair[i].num1->val - vec_pair[i].num2->val);
   }

   return sum;
}


void MinSum::print_pair() {
   for (int i = 0; i < vec_pair.size(); i++) {
      cout << "(" << vec_pair[i].num1->flag << ", " << vec_pair[i].num2->flag << ") ";
   }

   cout << endl;
   for (int i = 0; i < vec_pair.size(); i++) {
      cout << "(" << vec_pair[i].num1->val << ", " << vec_pair[i].num2->val << ") ";
   }
   cout << endl;
}

int main() {
   MinSum ms;

   ms.make_vec();   
   ms.make_pair();

   cout << endl;
   ms.print_pair();

   cout << ms.min_abs() << endl;

}
// i don't know what to do nextㅜㅜ
