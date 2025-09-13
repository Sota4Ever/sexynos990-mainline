// SPDX-License-Identifier: GPL-2.0-only
/*
 * UFS PHY driver data for Exynos990 SoC
 *
 * Author: Igor Belwon <igor.belwon@mentallysanemainliners.org>
 * Author: Denzeel Oliva <wachiturroxd150@gmail.com>
 *
 */

#include "phy-samsung-ufs.h"

#define EXYNOS990_PHY_CTRL			0x724
#define EXYNOS990_PHY_CTRL_MASK			0x1
#define EXYNOS990_PHY_CTRL_EN			BIT(0)
#define PHY_EXYNOS990_LANE_OFFSET		0x800
#define TRSV_REG338				0x338
#define LN0_MON_RX_CAL_DONE			BIT(3)
#define TRSV_REG339				0x339
#define LN0_MON_RX_CDR_FLD_CK_MODE_DONE		BIT(3)
#define TRSV_REG222				0x222
#define LN0_OVRD_RX_CDR_EN			BIT(4)
#define LN0_RX_CDR_EN				BIT(3)

#define PHY_PMA_TRSV_ADDR(reg, lane)	(PHY_APB_ADDR((reg) + \
					((lane) * PHY_EXYNOS990_LANE_OFFSET)))

#define PHY_TRSV_REG_CFG_EXYNOS990(o, v, d) \
	PHY_TRSV_REG_CFG_OFFSET(o, v, d, PHY_EXYNOS990_LANE_OFFSET)

/* Calibration for phy initialization */
static const struct samsung_ufs_phy_cfg exynos990_pre_init_cfg[] = {
	PHY_COMN_REG_CFG(0x43, 0x10, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x46, 0x48, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x207, 0x0c, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2E1, 0x40, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x25D, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x25E, 0x36, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x25F, 0xdb, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x264, 0x4e, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x26E, 0x5e, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x26F, 0x70, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2ED, 0x25, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2AC, 0x23, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x279, 0xf0, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x273, 0x03, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2F4, 0x2f, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2B3, 0x05, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2B6, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2B7, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2B8, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2B9, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2BA, 0x0b, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2BB, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2BC, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2BD, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2BE, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x307, 0x21, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x274, 0x50, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x234, 0x60, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x0A, 0x33, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x0D, 0xb9, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x0E, 0x0f, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x11, 0x01, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x2C, 0x30, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x41, 0x20, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x13, 0x12, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x48, 0x0a, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2E4, 0x1a, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x43, 0x18, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x43, 0x00, PWR_MODE_ANY),
	END_UFS_PHY_CFG,

};

static const struct samsung_ufs_phy_cfg exynos990_post_init_cfg[] = {
	PHY_COMN_REG_CFG(0x43, 0x10, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2E1, 0xc0, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x200, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x201, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x202, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x203, 0x0a, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x204, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x205, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x23C, 0x6e, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x239, 0x5a, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x240, 0x58, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2A2, 0x04, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x27D, 0x01, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2FA, 0x01, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x284, 0x04, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x285, 0x06, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x288, 0x00, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x289, 0x02, PWR_MODE_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x22D, 0xb8, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x43, 0x18, PWR_MODE_ANY),
	PHY_COMN_REG_CFG(0x43, 0x00, PWR_MODE_ANY),
	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg exynos990_pre_pwr_hs_config[] = {
	PHY_TRSV_REG_CFG_EXYNOS990(0x206, 0x20, PWR_MODE_HS_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2F1, 0x07, PWR_MODE_HS_G1_SER_B |
						PWR_MODE_HS_G2_SER_B),
	PHY_TRSV_REG_CFG_EXYNOS990(0x2F2, 0x3f, PWR_MODE_HS_G3_SER_B |
						PWR_MODE_HS_G4_SER_B),
	PHY_TRSV_REG_CFG_EXYNOS990(0x246, 0x03, PWR_MODE_HS_ANY),
	END_UFS_PHY_CFG,
};

/* Calibration for HS mode series A/B */
static const struct samsung_ufs_phy_cfg exynos990_post_pwr_hs_config[] = {
	PHY_COMN_REG_CFG(0x8, 0x60, PWR_MODE_PWM_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x222, 0x08, PWR_MODE_PWM_ANY),
	PHY_TRSV_REG_CFG_EXYNOS990(0x246, 0x01, PWR_MODE_ANY),
	END_UFS_PHY_CFG,
};

static const struct samsung_ufs_phy_cfg *exynos990_ufs_phy_cfgs[CFG_TAG_MAX] = {
	[CFG_PRE_INIT]		= exynos990_pre_init_cfg,
	[CFG_POST_INIT]		= exynos990_post_init_cfg,
	[CFG_PRE_PWR_HS]	= exynos990_pre_pwr_hs_config,
	[CFG_POST_PWR_HS]	= exynos990_post_pwr_hs_config,
};

static const char * const exynos990_ufs_phy_clks[] = {
	"ref_clk",
};

static int exynos990_phy_wait_for_calibration(struct phy *phy, u8 lane)
{
	struct samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	const unsigned int timeout_us = 40000;
	const unsigned int sleep_us = 40;
	u32 val;
	u32 off;
	int err;

	off = PHY_PMA_TRSV_ADDR(TRSV_REG338, lane);

	err = readl_poll_timeout(ufs_phy->reg_pma + off,
				 val, (val & LN0_MON_RX_CAL_DONE),
				 sleep_us, timeout_us);

	if (err) {
		dev_err(ufs_phy->dev,
			"failed to get phy cal done %d\n", err);
	}

	return err;
}

#define DELAY_IN_US	40
#define RETRY_CNT	100
static int exynos990_phy_wait_for_cdr_lock(struct phy *phy, u8 lane)
{
	struct samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	u32 val;
	int i;

	for (i = 0; i < RETRY_CNT; i++) {
		udelay(DELAY_IN_US);
		val = readl(ufs_phy->reg_pma +
			    PHY_PMA_TRSV_ADDR(TRSV_REG339, lane));

		if (val & LN0_MON_RX_CDR_FLD_CK_MODE_DONE)
			return 0;

		udelay(DELAY_IN_US);
		/* Override and enable clock data recovery */
		writel(LN0_OVRD_RX_CDR_EN, ufs_phy->reg_pma +
		       PHY_PMA_TRSV_ADDR(TRSV_REG222, lane));
		writel(LN0_OVRD_RX_CDR_EN | LN0_RX_CDR_EN,
		       ufs_phy->reg_pma + PHY_PMA_TRSV_ADDR(TRSV_REG222, lane));
	}
	dev_err(ufs_phy->dev, "failed to get cdr lock\n");
	return -ETIMEDOUT;
}

const struct samsung_ufs_phy_drvdata exynos990_ufs_phy = {
	.cfgs = exynos990_ufs_phy_cfgs,
	.isol = {
		.offset = EXYNOS990_PHY_CTRL,
		.mask = EXYNOS990_PHY_CTRL_MASK,
		.en = EXYNOS990_PHY_CTRL_EN,
	},
	.clk_list = exynos990_ufs_phy_clks,
	.num_clks = ARRAY_SIZE(exynos990_ufs_phy_clks),
	.wait_for_cal = exynos990_phy_wait_for_calibration,
	.wait_for_cdr = exynos990_phy_wait_for_cdr_lock,
};
