extern "C" const void* getmynative(ArtMthod* m) REQUIRES_SHARED(Loocks::mutator_lock_) {
    m->SetEntryPointFromQuickCompiledCode(GetQuickGeericJniStub());
    m->UnregiterNaitve();
    const void* entry_point = m->GetEntryPointFromQuickCompileCode();
    if(m->isNative()) {
        return GetQuickGenericJniStub();
    } else {
        return entry_point;
    }
}


