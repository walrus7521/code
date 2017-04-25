

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

+
+#define BUILD_BUG_ON( x ) \
+  switch ( x ) \
+  { \
+  case false: \
+    break; \
+  case ( x ): \
+    break; \
+  }
+
+void ADPCheckSize()
+{
+    BUILD_BUG_ON(sizeof(ADP_CLAW_COEFF_STRUCT)          == 1712);
+    BUILD_BUG_ON(sizeof(MODE_LOGIC_COEFF_STRUCT)        == 36);
+    BUILD_BUG_ON(sizeof(COMMAND_SYNC_COEFF_STRUCT)      == 88);
+    BUILD_BUG_ON(sizeof(ROLL_CONTROL_COEFF_STRUCT)      == 112);
+    BUILD_BUG_ON(sizeof(PITCH_CONTROL_COEFF_STRUCT)     == 112);
+    BUILD_BUG_ON(sizeof(TWO_DIMENSIONAL_LINTERP_STRUCT) == 1364);
+}
+

