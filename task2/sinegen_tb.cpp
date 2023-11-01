#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsinegen.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i; // clock count
    int tick; // 

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vsinegen* top = new Vsinegen;

    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open("sinegen.vcd");

    top->clk = 1;
    top->rst = 0;
    top->en = 1;
    top->incr = 1;

    if (vbdOpen()!=1) return(-1);
    vbdHeader("L2T1: SigGen");

    for (i=0; i < 1000000; i++)
    {

        for (tick=0; tick<2; tick++) {
            tfp->dump (2*i+tick);
            top->clk = !top->clk;
            top->eval ();
        }
        
        top->incr = vbdValue();

        vbdPlot(int (top->dout1), 0, 255);
        vbdPlot(int (top->dout2), 0, 255);
        vbdCycle(i);

        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
            exit(0); 
    }

    vbdClose();   
    tfp->close(); 
    exit(0);
}