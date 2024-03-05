#pragma once

namespace constants {

constexpr std::pair<unsigned short, const char*> kQweatherIconMap[]                     = {{100, u8"\uf101"}, {101, u8"\uf102"}, {102, u8"\uf103"}, {103, u8"\uf104"}, {104, u8"\uf105"}, {150, u8"\uf106"}, {151, u8"\uf107"}, {152, u8"\uf108"}, {153, u8"\uf109"}, {300, u8"\uf10a"}, {301, u8"\uf10b"}, {302, u8"\uf10c"}, {303, u8"\uf10d"}, {304, u8"\uf10e"}, {305, u8"\uf10f"}, {306, u8"\uf110"}, {307, u8"\uf111"}, {308, u8"\uf112"}, {309, u8"\uf113"}, {310, u8"\uf114"}, {311, u8"\uf115"}, {312, u8"\uf116"}, {313, u8"\uf117"}, {314, u8"\uf118"}, {315, u8"\uf119"}, {316, u8"\uf11a"}, {317, u8"\uf11b"}, {318, u8"\uf11c"}, {350, u8"\uf11d"}, {351, u8"\uf11e"}, {399, u8"\uf11f"}, {400, u8"\uf120"}, {401, u8"\uf121"}, {402, u8"\uf122"}, {403, u8"\uf123"}, {404, u8"\uf124"}, {405, u8"\uf125"}, {406, u8"\uf126"}, {407, u8"\uf127"}, {408, u8"\uf128"}, {409, u8"\uf129"}, {410, u8"\uf12a"}, {456, u8"\uf12b"}, {457, u8"\uf12c"}, {499, u8"\uf12d"}, {500, u8"\uf12e"}, {501, u8"\uf12f"}, {502, u8"\uf130"}, {503, u8"\uf131"}, {504, u8"\uf132"}, {507, u8"\uf133"}, {508, u8"\uf134"}, {509, u8"\uf135"}, {510, u8"\uf136"}, {511, u8"\uf137"}, {512, u8"\uf138"}, {513, u8"\uf139"}, {514, u8"\uf13a"}, {515, u8"\uf13b"}, {800, u8"\uf13c"}, {801, u8"\uf13d"}, {802, u8"\uf13e"}, {803, u8"\uf13f"}, {804, u8"\uf140"}, {805, u8"\uf141"}, {806, u8"\uf142"}, {807, u8"\uf143"}, {900, u8"\uf144"}, {901, u8"\uf145"}, {999, u8"\uf146"}, {1001, u8"\uf147"}, {1002, u8"\uf148"}, {1003, u8"\uf149"}, {1004, u8"\uf14a"}, {1005, u8"\uf14b"}, {1006, u8"\uf14c"}, {1007, u8"\uf14d"}, {1008, u8"\uf14e"}, {1009, u8"\uf14f"}, {1010, u8"\uf150"}, {1011, u8"\uf151"}, {1012, u8"\uf152"}, {1013, u8"\uf153"}, {1014, u8"\uf154"}, {1015, u8"\uf155"}, {1016, u8"\uf156"}, {1017, u8"\uf157"}, {1018, u8"\uf158"}, {1019, u8"\uf159"}, {1020, u8"\uf15a"}, {1021, u8"\uf15b"}, {1022, u8"\uf15c"}, {1023, u8"\uf15d"}, {1024, u8"\uf15e"}, {1025, u8"\uf15f"}, {1026, u8"\uf160"}, {1027, u8"\uf161"}, {1028, u8"\uf162"}, {1029, u8"\uf163"}, {1030, u8"\uf164"}, {1031, u8"\uf165"}, {1032, u8"\uf166"}, {1033, u8"\uf167"}, {1034, u8"\uf168"}, {1035, u8"\uf169"}, {1036, u8"\uf16a"}, {1037, u8"\uf16b"}, {1038, u8"\uf16c"}, {1039, u8"\uf16d"}, {1040, u8"\uf16e"}, {1041, u8"\uf16f"}, {1042, u8"\uf170"}, {1043, u8"\uf171"}, {1044, u8"\uf172"}, {1045, u8"\uf173"}, {1046, u8"\uf174"}, {1047, u8"\uf175"}, {1048, u8"\uf176"}, {1049, u8"\uf177"}, {1050, u8"\uf178"}, {1051, u8"\uf179"}, {1052, u8"\uf17a"}, {1053, u8"\uf17b"}, {1054, u8"\uf17c"}, {1055, u8"\uf17d"}, {1056, u8"\uf17e"}, {1057, u8"\uf17f"}, {1058, u8"\uf180"}, {1059, u8"\uf181"}, {1060, u8"\uf182"}, {1061, u8"\uf183"}, {1062, u8"\uf184"}, {1063, u8"\uf185"}, {1064, u8"\uf186"}, {1065, u8"\uf187"}, {1066, u8"\uf188"}, {1067, u8"\uf189"}, {1068, u8"\uf18a"}, {1069, u8"\uf18b"}, {1071, u8"\uf18c"}, {1072, u8"\uf18d"}, {1073, u8"\uf18e"}, {1074, u8"\uf18f"}, {1075, u8"\uf190"}, {1076, u8"\uf191"}, {1077, u8"\uf192"}, {1078, u8"\uf193"}, {1079, u8"\uf194"}, {1080, u8"\uf195"}, {1081, u8"\uf196"}, {1082, u8"\uf197"}, {1084, u8"\uf198"}, {1085, u8"\uf199"}, {1086, u8"\uf19a"}, {1087, u8"\uf19b"}, {1088, u8"\uf19c"}, {1089, u8"\uf19d"}, {1101, u8"\uf19e"}, {1302, u8"\uf19f"}, {1402, u8"\uf1a0"}, {1601, u8"\uf1a1"}, {1602, u8"\uf1a2"}, {1603, u8"\uf1a3"}, {1604, u8"\uf1a4"}, {1605, u8"\uf1a5"}, {1606, u8"\uf1a6"}, {1607, u8"\uf1a7"}, {1701, u8"\uf1a8"}, {1702, u8"\uf1a9"}, {1703, u8"\uf1aa"}, {2001, u8"\uf1ab"}, {2002, u8"\uf1ac"}, {2003, u8"\uf1ad"}, {2004, u8"\uf1ae"}, {2005, u8"\uf1af"}, {2006, u8"\uf1b0"}, {2007, u8"\uf1b1"}, {2008, u8"\uf1b2"}, {2009, u8"\uf1b3"}, {2010, u8"\uf1b4"}, {2011, u8"\uf1b5"}, {2012, u8"\uf1b6"}, {2013, u8"\uf1b7"}, {2014, u8"\uf1b8"}, {2015, u8"\uf1b9"}, {2016, u8"\uf1ba"}, {2017, u8"\uf1bb"}, {2018, u8"\uf1bc"}, {2019, u8"\uf1bd"}, {2020, u8"\uf1be"}, {2021, u8"\uf1bf"}, {2022, u8"\uf1c0"}, {2023, u8"\uf1c1"}, {2024, u8"\uf1c2"}, {2025, u8"\uf1c3"}, {2026, u8"\uf1c4"}, {2027, u8"\uf1c5"}, {2028, u8"\uf1c6"}, {2052, u8"\uf1c7"}, {2053, u8"\uf1c8"}, {2054, u8"\uf1c9"}, {9998, u8"\uf1ca"}, {9999, u8"\uf1cb"}};
constexpr const char                             kQweatherApiUrl[]                      = "https://devapi.qweather.com/v7/weather/7d?key=%1&location=%2";

constexpr const char                             kTimeFormat[]                          = "HH:mm:ss";
constexpr const char                             kDateWeekdayFormat[]                   = "M月d日 dddd";
constexpr const char                             kSentenceAuthorFormat[]                = "——%1";
constexpr const char                             kNoticeDateFormat[]                    = "至M月d日";
constexpr const char                             kLessonFormat[]                        = "%1 (%2~%3)";
constexpr const char                             kStudentNameFormat[]                   = "%1号%2";
constexpr const char                             kTemptureFormat[]                      = "%1℃~%2℃";
constexpr const char                             kRollCallUncalledFormat[]              = "未抽到：%1人";
constexpr const char                             kTransferDateFormat[]                  = "yyyyMMdd";
constexpr const char                             kTransferTimeFormat[]                  = "HHmm";

constexpr int                                    kClockTimerIntervalMs                  = 1'000;
constexpr int                                    kSentencesNoticesSwitchTimerIntervalMs = 30'000;
constexpr int                                    kRollCallTimerIntervalMs               = 180;

}  // namespace constants
