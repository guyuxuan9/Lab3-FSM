#include "Vlfsr4.h" // for module counter
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc,char **argv,char **env)
{
    int i; // i counts the number of clock cycles to simulate
    int clk; // clock signal, 1 or 0

    Verilated::commandArgs(argc,argv);

    // init top verilog instance
    // instantiate the counter as Vcounter, which is the name of all generated files. This is the DUT.
    Vlfsr4* top = new Vlfsr4;
    // init trace dump
    // trun on signal tracing
    Verilated::traceEverOn(true);
    // tell verilator to dump the waveform data to counter.vcd
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp,99);
    tfp->open("lfsr4.vcd");

    // init vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader("L3T1: lfsr7");

    // initialise simulation inputs
    top -> clk = 1;
    top -> rst = 0;
    top -> en = 0;
    
    // vbdSetMode(1) is used to increment the counter each time the switch is pressed
    vbdSetMode(1);
    
    // run the simulation for many clock cycles
    for (i=0;i<300;i++)
    {   top -> rst = (i<2);
        top -> en = vbdFlag();
        // dump variables into VCD file and toggle clock
        for (clk=0;clk<2;clk++)
        {
            tfp -> dump(2*i+clk); // unit is in ps!
            top -> clk = !top -> clk;
            top -> eval();
        }
        vbdHex(2,(int(top->data_out)>>4) & 0xF);
        vbdHex(1,int(top->data_out) & 0xF);
        //vbdBar(top->data_out & 0xFF);
        vbdCycle(i+1);        
        if (Verilated::gotFinish()) exit(0);
    }
    vbdClose();
    tfp->close();
    exit(0);
}