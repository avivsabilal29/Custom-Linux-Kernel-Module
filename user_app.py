def main():
    driver_handle = open("/proc/sabilal_driver")
    message = driver_handle.readline()
    print(F"Message: {message}")
main()