#include <vpi_user.h>

static int traffic_compiletf(char* user_data)
{
    vpi_printf("cplt: %s\n", user_data);
    return 0;
}

static int traffic_calltf(char* user_data)
{
    vpi_printf("call: %s\n", user_data);
    vpi_printf("Traffic lights!\n");
    return 0;
}

void traffic_register()
{
      s_vpi_systf_data tf_data;

      tf_data.type      = vpiSysTask;
      tf_data.tfname    = "$traffic";
      tf_data.calltf    = traffic_calltf;
      tf_data.compiletf = traffic_compiletf;
      tf_data.sizetf    = 0;
      tf_data.user_data = 0;
      vpi_register_systf(&tf_data);
}

void (*vlog_startup_routines[])() = {
    traffic_register, 0
};
