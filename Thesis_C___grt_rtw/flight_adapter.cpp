#include "Thesis_C__.h"
#include "rtw_solver.h"

// Global instance
static Thesis_C__ modelObj;

extern "C" {

    void Thesis_C___initialize() {
        modelObj.initialize();
    }

    void Thesis_C___step() {
        modelObj.step();
    }

    void Thesis_C___terminate() {
        Thesis_C__::terminate();
    }

    void set_inputs(double* u_ptr) {
        if (u_ptr == nullptr) return;

        ExtU_Thesis_C___T inputStruct;
        for(int i=0; i<5; i++) {
             if (i < 4) inputStruct.In1[i] = u_ptr[i];
             else inputStruct.In1[i] = 0.0;
        }
        modelObj.setExternalInputs(&inputStruct);
    }

    void get_outputs(double* y_ptr) {
        if (y_ptr == nullptr) return;

        const ExtY_Thesis_C___T& outputStruct = modelObj.getExternalOutputs();
        for(int i=0; i<9; i++) {
            y_ptr[i] = (double)outputStruct.Out1[i];
        }
    }
}