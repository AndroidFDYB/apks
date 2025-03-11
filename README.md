# 内容
1. APKS  和 热修复、插件化相关
2. HOOK 测试
   3. JavaHook: Shark.eat()
      4. ClassLinker::defineClass --> 
                  ClassLinker::LoadMethod(dex_file,it,class,ArtMethod) -->
                        LinkCode(classLinker,method,oat_clas,class_def_method_index)
                              -a--> static          quick_resolve_stub
                              -b--> native          generic_jni_stub
                                       method.UnRegisterNative
                                       GetJniDlSymLookupStub() ---> ark_quick_jni_trampoline
                              -c--> interceptor     quick_interceptor_bridge
                                       art_quick_to_interceptor_bridge , 这是汇编代码
      5. 