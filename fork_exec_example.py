import os
import sys
import time
def main():
    print(f"Parent process starting (PID: {os.getpid()})")
    try:
        pid = os.fork()
    except OSError as e:
        print(f"Fork Failed: {e}")
        sys.exit(1)
    if pid < 0:
        print("Fork Failed")
        sys.exit(1)
    elif pid == 0:
        print(f"Child process created (PID: {os.getpid()}, Parent PID: {os.getppid()})")
        print("Child process executing: ls -la")
        try:
            os.execvp("ls", ["ls", "-la"])
        except OSError as e:
            print(f"execvp failed: {e}")
            sys.exit(1)
    else:
        print(f"Parent process waiting for child (Child PID: {pid})")
        try:
            child_pid, exit_status = os.wait()
            print(f"Child process {child_pid} completed")
            if os.WIFEXITED(exit_status):
                exit_code = os.WEXITSTATUS(exit_status)
                print(f"Child Complete with exit status: {exit_code}")
            else:
                print("Child process terminated abnormally")
        except OSError as e:
            print(f"Wait failed: {e}")
            sys.exit(1)
if __name__ == "__main__":
    main()