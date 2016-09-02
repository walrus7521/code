#include <cstdint>
#include <atomic>
#include <mutex>
#include <memory>

// https://github.com/facebook/folly/tree/master/folly

namespace fruitcake {

template<typename T>
class ListNode {
  enum {
    IS_HEAD_NODE = 1,
    MARKED_FOR_REMOVAL = (1 << 1),
    FULLY_LINKED = (1 << 2),
  };

 public:
  typedef T value_type;

  template<typename NodeAlloc, typename U,
    typename=typename std::enable_if<std::is_convertible<U, T>::value>::type>  

  static ListNode* create(
          NodeAlloc& alloc, int height, U&& data, bool isHead = false) {
      size_t size = sizeof(ListNode) +
        height * sizeof(std::atomic<ListNode*>);
      auto* node = static_cast<ListNode*>(alloc.allocate(size));
      // do placement new
      new (node) ListNode(height, std::forward<U>(data), isHead);
      return node;
  }

  std::unique_lock<std::mutex> acquireGuard() {
    return std::unique_lock<std::mutex>(spinLock_);
  }

  bool fullyLinked() const      { return getFlags() & FULLY_LINKED; }
  bool markedForRemoval() const { return getFlags() & MARKED_FOR_REMOVAL; }
  bool isHeadNode() const       { return getFlags() & IS_HEAD_NODE; }

  void setIsHeadNode() {
    setFlags(getFlags() | IS_HEAD_NODE);
  }
  void setFullyLinked() {
    setFlags(getFlags() | FULLY_LINKED);
  }
  void setMarkedForRemoval() {
    setFlags(getFlags() | MARKED_FOR_REMOVAL);
  }  

 private:
  std::atomic<uint16_t> flags_;
  std::mutex spinLock_;

  uint16_t getFlags() const {
    // atomically obtain value
    return flags_.load(std::memory_order_consume);
  }

  void setFlags(uint16_t flags) {
    // atomically replace the value
    flags_.store(flags, std::memory_order_release);
  }
};

}

using namespace fruitcake;

void test(ListNode<int> *node)
{
    node->acquireGuard();
}

int main()
{
    uint16_t u = 0;
    ListNode<int> *head = new ListNode<int>();
    //ListNode<int> *node = ListNode<>::create();
    head->setIsHeadNode();
    test(head);
    return 0;
}

