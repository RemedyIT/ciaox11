Testing the type name

The original type in DDS4CCM will be generated in a new IDL file
in the DDS::Native namespace:

struct X {
  short Y;
};

will be supplied to the DDS generator as

DDS
{
  Native
  {
    struct X {
      short Y;
    };
  };
};

In order to be compatible with other DDS applications, the type name supplied to
DDS should be X (and NOT DDS::Native::X).

This test tests whether this is the case.
