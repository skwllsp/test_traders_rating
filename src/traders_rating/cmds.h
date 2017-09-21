#ifndef traders_rating_cmds_h
#define traders_rating_cmds_h

#include <string>
#include <memory>
#include <functional>

namespace traders_rating {

using user_id_t = uint64_t;
using amount_t = double;
using user_name_t = std::string;

/*
 *
 */
class cmd {
 public:
  virtual ~cmd() {};
  virtual void handle() = 0;
};
using cmd_uptr = std::unique_ptr<cmd>;

/*
 *
 */
using user_registered_handler = std::function<void(user_id_t, user_name_t)>;

class user_registered : public cmd {
 public:
  user_registered(user_id_t, const user_name_t&,
                  user_registered_handler);

 private:
  user_id_t id;
  user_name_t user_name;
  user_registered_handler handler;

 private:
  void handle() override;
};

/*
 *
 */
using user_deal_won_handler = std::function<void(time_t, user_id_t, amount_t)>;

class user_deal_won : public cmd {
 public:
  user_deal_won(time_t, user_id_t, amount_t,
                user_deal_won_handler);

 private:
  time_t ts;
  user_id_t id;
  amount_t amount;
  user_deal_won_handler handler;

 private:
  void handle() override;
};

}  // namespace traders_rating

#endif  // traders_rating_cmds_h
