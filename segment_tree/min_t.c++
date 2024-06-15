//credits:galencolin
struct min_t {
  long long val;
  static const long long null_v =LLONG_MAX;

  min_t(): val(0) {}
  min_t(long long v): val(v) {}

  min_t op(min_t& other) {
    return min_t(min(val, other.val));
  }
  
  min_t lazy_op(min_t& v, int size) {
    return min_t(val + v.val);
  }
};