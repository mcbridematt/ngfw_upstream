// quited from ixgbe_type.h

/* General Registers */
#define IXGBE_CTRL              0x00000
#define IXGBE_STATUS            0x00008
#define IXGBE_CTRL_EXT          0x00018
#define IXGBE_ESDP              0x00020
#define IXGBE_EODSDP            0x00028
#define IXGBE_I2CCTL            0x00028
#define IXGBE_PHY_GPIO          0x00028
#define IXGBE_MAC_GPIO          0x00030
#define IXGBE_PHYINT_STATUS0    0x00100
#define IXGBE_PHYINT_STATUS1    0x00104
#define IXGBE_PHYINT_STATUS2    0x00108
#define IXGBE_LEDCTL            0x00200
#define IXGBE_FRTIMER           0x00048
#define IXGBE_TCPTIMER          0x0004C
#define IXGBE_CORESPARE         0x00600
#define IXGBE_EXVET             0x05078
/* MAC Registers */
#define IXGBE_MSCA              0x0425C
#define IXGBE_MSRWD             0x04260
/* MSCA Bit Masks */
#define IXGBE_MSCA_NP_ADDR_MASK         0x0000FFFF      /* MDI Addr (new prot) */
#define IXGBE_MSCA_NP_ADDR_SHIFT        0
#define IXGBE_MSCA_DEV_TYPE_MASK        0x001F0000      /* Dev Type (new prot) */
#define IXGBE_MSCA_DEV_TYPE_SHIFT       16              /* Register Address (old prot */
#define IXGBE_MSCA_PHY_ADDR_MASK        0x03E00000      /* PHY Address mask */
#define IXGBE_MSCA_PHY_ADDR_SHIFT       21              /* PHY Address shift*/
#define IXGBE_MSCA_OP_CODE_MASK         0x0C000000      /* OP CODE mask */
#define IXGBE_MSCA_OP_CODE_SHIFT        26              /* OP CODE shift */
#define IXGBE_MSCA_ADDR_CYCLE           0x00000000      /* OP CODE 00 (addr cycle) */
#define IXGBE_MSCA_WRITE                0x04000000      /* OP CODE 01 (wr) */
#define IXGBE_MSCA_READ                 0x0C000000      /* OP CODE 11 (rd) */
#define IXGBE_MSCA_READ_AUTOINC         0x08000000      /* OP CODE 10 (rd auto inc)*/
#define IXGBE_MSCA_ST_CODE_MASK         0x30000000      /* ST Code mask */
#define IXGBE_MSCA_ST_CODE_SHIFT        28              /* ST Code shift */
#define IXGBE_MSCA_NEW_PROTOCOL         0x00000000      /* ST CODE 00 (new prot) */
#define IXGBE_MSCA_OLD_PROTOCOL         0x10000000      /* ST CODE 01 (old prot) */
#define IXGBE_MSCA_MDI_COMMAND          0x40000000      /* Initiate MDI command */
#define IXGBE_MSCA_MDI_IN_PROG_EN       0x80000000      /* MDI in progress ena */
/* MSRWD bit masks */
#define IXGBE_MSRWD_WRITE_DATA_MASK     0x0000FFFF
#define IXGBE_MSRWD_WRITE_DATA_SHIFT    0
#define IXGBE_MSRWD_READ_DATA_MASK      0xFFFF0000
#define IXGBE_MSRWD_READ_DATA_SHIFT     16


