#ifndef DEF_H_
#define DEF_H_

// Files to use
#define		OUT_FILE		    "txts/all.txt"
#define 	AGES_FILE		    "txts/ages.txt"
#define		SEXES_FILE		    "txts/sexes.txt"
#define 	HTA_FILE		    "txts/hta.txt"
#define		HSA_FILE		    "txts/hsa.txt"
#define     RANK_FILE           "txts/rankin.txt"
#define     GLASG_FILE          "txts/glasgow.txt"
#define		INC_FILE		    "txts/incid.txt"
#define 	TREATMENT_FILE		"txts/treatment.txt"

typedef enum param_type
{
    AGE     = 0x00000001,
    SEX     = 0x00000002,
    HTA     = 0x00000004,
    HSA     = 0x00000008,
    INC     = 0x00000010,
    RANK    = 0x00000020,
    GLASG   = 0x00000040,
    TREAT   = 0x00000080,
} param_t;

#endif /* DEF_H_ */
