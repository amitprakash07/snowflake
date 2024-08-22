#ifndef ENGINE_COMMON_UNIQUE_PTR
#define ENGINE_COMMON_UNIQUE_PTR

namespace engine {
template <typename T>
class UniquePtr {
 public:
  UniquePtr();
  bool deleteObject();
  ~UniquePtr();
  UniquePtr(UniquePtr&);
  UniquePtr& operator=(UniquePtr&);
  T& operator*();
  T* operator->();

 private:
  T* m_WrappingObject;
};  // UniquePtr
}  
#endif  // header guard