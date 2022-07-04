#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"

enum Vouchers
{
    GIFT_VOUCHER_HUMAN        = 14646,
    GIFT_VOUCHER_DWARF_GNOME  = 14647,
    GIFT_VOUCHER_NIGHTELF     = 14648,
    GIFT_VOUCHER_ORC_TROLL    = 14649,
    GIFT_VOUCHER_TAUREN       = 14650,
    GIFT_VOUCHER_UNDEAD       = 14651,
    GIFT_VOUCHER_BLOODELF     = 20938,
    GIFT_VOUCHER_DRAENEI      = 22888,
    GIFT_VOUCHER_DEATH_KNIGHT = 39713,
};

class GiftVouchers : public PlayerScript
{
public:
    GiftVouchers() : PlayerScript("GiftVouchers") {}

    void OnLogin(Player* player) override
    {
        if (!isCharacterValid(player))
            return;

        if (player->GetFreeInventorySpace() == 0)
            return;

        if (player->getClass() == CLASS_DEATH_KNIGHT)
        {
            player->AddItem(GIFT_VOUCHER_DEATH_KNIGHT, 1);
        }
        else
        {
            switch (player->getRace())
            {
                case RACE_HUMAN:
                    player->AddItem(GIFT_VOUCHER_HUMAN, 1);
                    break;
                case RACE_DWARF:
                case RACE_GNOME:
                    player->AddItem(GIFT_VOUCHER_DWARF_GNOME, 1);
                    break;
                case RACE_NIGHTELF:
                    player->AddItem(GIFT_VOUCHER_NIGHTELF, 1);
                    break;
                case RACE_DRAENEI:
                    player->AddItem(GIFT_VOUCHER_DRAENEI, 1);
                    break;
                case RACE_ORC:
                case RACE_TROLL:
                    player->AddItem(GIFT_VOUCHER_ORC_TROLL, 1);
                    break;
                case RACE_UNDEAD_PLAYER:
                    player->AddItem(GIFT_VOUCHER_UNDEAD, 1);
                    break;
                case RACE_TAUREN:
                    player->AddItem(GIFT_VOUCHER_TAUREN, 1);
                    break;
                case RACE_BLOODELF:
                    player->AddItem(GIFT_VOUCHER_BLOODELF, 1);
                    break;
                default:
                    break;
            }
        }

        QueryResult result = LoginDatabase.Query("REPLACE INTO `gift_vouchers` (`account_id`, `realm_id`, `character_guid`) VALUES ({}, {}, {})", player->GetSession()->GetAccountId(), sConfigMgr->GetOption<uint32>("RealmID", 0), player->GetGUID().GetCounter());
    }

private:
    bool isCharacterValid(Player* player)
    {
        QueryResult result = LoginDatabase.Query("SELECT * FROM `gift_vouchers` WHERE `account_id` = {} AND `realm_id` = {} AND `character_guid` = {}", player->GetSession()->GetAccountId(), sConfigMgr->GetOption<uint32>("RealmID", 0), player->GetGUID().GetCounter());

        if (!result)
            return true;

        return false;
    }
};

void AddGiftVouchersScripts()
{
    new GiftVouchers();
}
