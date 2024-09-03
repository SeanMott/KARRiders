
int (*OSReport)(char *__format,...) = (int *)0x803d4ce8;

///
///
///
void OnInit(int *rider_data)
{
    OSReport("Initializing Gooey %8X\n", rider_data);
}
