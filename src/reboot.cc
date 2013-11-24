#include <unistd.h>
#include <v8.h>
#include <node.h>
#include <cstring>

// LINUX_REBOOT_CMD_RESTART
#include <linux/reboot.h>

// reboot()
#include <sys/reboot.h>

//http://linux.die.net/man/2/reboot

using namespace std;
using namespace v8;
using namespace node;

namespace NodeOS
{
  
  static Handle<Object> GetRebootFlags() {
    HandleScope scope;
    
    Local<Object> flags = Object::New();
    
    flags->Set( String::New("LINUX_REBOOT_CMD_CAD_OFF"), Integer::New(LINUX_REBOOT_CMD_CAD_OFF) );
    flags->Set( String::New("LINUX_REBOOT_CMD_CAD_ON"), Integer::New(LINUX_REBOOT_CMD_CAD_ON) );
    flags->Set( String::New("LINUX_REBOOT_CMD_HALT"), Integer::New(LINUX_REBOOT_CMD_HALT) );
    flags->Set( String::New("LINUX_REBOOT_CMD_KEXEC"), Integer::New(LINUX_REBOOT_CMD_KEXEC) );
    flags->Set( String::New("LINUX_REBOOT_CMD_POWER_OFF"), Integer::New(LINUX_REBOOT_CMD_POWER_OFF) );
    flags->Set( String::New("LINUX_REBOOT_CMD_RESTART"), Integer::New(LINUX_REBOOT_CMD_RESTART) );
    flags->Set( String::New("LINUX_REBOOT_CMD_RESTART2"), Integer::New(LINUX_REBOOT_CMD_RESTART2) );
    
    return scope.Close(flags);
  }
  
  static Handle<Value> Reboot(const Arguments& args) {
    HandleScope scope;
    
    unsigned long command = Local<Number>::Cast(args[0])->Value();
    
    int res = reboot(command);
    
    return scope.Close(Integer::New(res));
  }
  
  static void init(Handle<Object> target) {
    target->Set(String::NewSymbol("flags"), GetRebootFlags() );
    target->Set(String::NewSymbol("reboot"),
      FunctionTemplate::New(Reboot)->GetFunction());
  }
  
}

NODE_MODULE(binding, NodeOS::init)
