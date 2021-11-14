#ifndef INCLUDE_RESOURCES
#define INCLUDE_RESOURCES

#ifdef PLATFORM_WIN32
#ifdef BUILD_DEBUG
#define RES_DIR_ANIMATIONS  "../../assets/Animations/"
#define RES_DIR_BACKGROUNDS "../../assets/Backgrounds/"
#define RES_DIR_DATA        "../../assets/Data/"
#define RES_DIR_FONTS       "../../assets/Fonts/"
#define RES_DIR_IMAGES      "../../assets/Images/"
#define RES_DIR_SOUNDS      "../../assets/Sounds/"
#else
#define RES_DIR_ANIMATIONS  "Resources/Animations/"
#define RES_DIR_BACKGROUNDS "Resources/Backgrounds/"
#define RES_DIR_DATA        "Resources/Data/"
#define RES_DIR_FONTS       "Resources/Fonts/"
#define RES_DIR_IMAGES      "Resources/Images/"
#define RES_DIR_SOUNDS      "Resources/Sounds/"
#endif
#endif

#ifdef PLATFORM_WEB
#define RES_DIR_ANIMATIONS  "assets/Animations/"
#define RES_DIR_BACKGROUNDS "assets/Backgrounds/"
#define RES_DIR_DATA        "assets/Data/"
#define RES_DIR_FONTS       "assets/Fonts/"
#define RES_DIR_IMAGES      "assets/Images/"
#define RES_DIR_SOUNDS      "assets/Sounds/"
#endif

#endif // INCLUDE_RESOURCES
