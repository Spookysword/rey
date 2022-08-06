
// A color, AKA an array of 4 unsigned ints (R, G, B, A), all 0 -> 255.
#ifdef __cplusplus
    class Color {
    public:
        unsigned int r, g, b, a;
        Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
        Color(unsigned int r, unsigned int g, unsigned int b) {
        Color(r, g, b, 255);
    }
        Color() {
        Color(255, 255, 255, 255);
    }
        Color(Color* pColor) {
        r = pColor->r;
        g = pColor->g;
        b = pColor->b;
        a = pColor->a;
    }
        unsigned int operator[](int i) const {
        switch (i) {
            case 0:
                return r;
                break;
            case 1:
                return g;
                break;
            case 2:
                return b;
                break;
            case 3:
                return a;
                break;
            default:
                return 0.0f;
                break;
        }
    }
    };
#else
	typedef unsigned int Color[4];
#endif
	void setColor(Color* oldColor, Color newColor);
	// A texture, which is really just an ID of the texture.