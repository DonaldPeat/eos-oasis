#include "Players.hpp"

namespace Oasis {
    using namespace eosio;
    using std::string;

    class Players : public contract {
        using contract::contract;

        public:
            Players(account_name self):contract(self) {}

            //@abi action
            void add(const account_name account, string& username, uint64_t level) {

              //restrict action to account owner/ authorized account_name
              require_auth(account);

              //access 'player' table with object, code & scope
              playerIndex players(_self,_self);

              //verify account doesn't already exist
              auto iterator = players.find(account);
              eosio_assert(iterator == players.end(), "Address for account already exists");

              //add & initialize new player, account parameter is the storage account (payer)
              players.emplace(account, [&](auto& player){
                player.account_name = account;
                player.username = username;
                player.level = 1;
                player.health_points = 1000;
                player.energy_points = 1000;
              });

            }

            //@abi action
            void update(const account_name account) {

            }

            //@abi action
            void getplayer(const account_name account) {

            }

        private:

            //@abi table player i64
            struct player {
                uint64_t account_name;
                string username;
                uint64_t level;
                uint64_t health_points = 1000;
                uint64_t energy_points = 1000;

                uint64_t primary_key() const { return account_name; }

                EOSLIB_SERIALIZE(player, (account_name)(username)(level)(health_points)(energy_points))
            };

            typedef multi_index<N(player), player> playerIndex;
    };

    EOSIO_ABI(Players, (add)(update)(getplayer))
}
