#ifndef SANDBOX_CODING_PROBLEMS_INTERFACE_H
#define SANDBOX_CODING_PROBLEMS_INTERFACE_H

#include <type_traits>

class ICodingProblem {
 public:
  virtual void RunTests() = 0;
  virtual ~ICodingProblem() = default;
};

template <class ICodingProblemDerivedClass>
concept Problem =
    std::is_convertible_v<ICodingProblemDerivedClass*, ICodingProblem*>;

template <Problem P>
class ScopedProblemExecute {
 public:
  ScopedProblemExecute() : problem_(nullptr) {
    problem_ = new P();
    if (problem_) {
      problem_->RunTests();
    }
  }
  ~ScopedProblemExecute() { delete problem_; }

 private:
  ICodingProblem* problem_;
};

#define INSTANTIATE_PROBLEM(X) ScopedProblemExecute<X> ExecuteProblem_##X;

#endif