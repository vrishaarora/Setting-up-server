#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

class Triangle {
    private:
        int base;
        int height;
    public:
        void t_set_base(int b);
        void t_set_height(int t);
        double t_area();
};

#endif /* TRIANGLE_HPP */