#ifndef ENGINE_COMMON_UNIQUE_PTR
#define ENGINE_COMMON_UNIQUE_PTR

namespace engine {
template <typename T>
class UniquePtr {
 public:
  UniquePtr();
  bool deleteObject();
  ~UniquePtr();
  UniquePtr(const UniquePtr&);
  UniquePtr& operator=(const UniquePtr&);
  T& operator*();
  T* operator->();

  UniquePtr(UniquePtr&&) = default;
  UniquePtr& operator=(UniquePtr&&) = default;

 private:
  T* m_WrappingObject;
};  // UniquePtr
}  // namespace engine
#endif  // header guard