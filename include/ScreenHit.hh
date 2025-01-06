#ifndef SCREEN_HH
#define SCREEN_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class ScreenHit : public G4VHit
{
  public:
    ScreenHit() = default;
    ScreenHit(const ScreenHit&) = default;
    ~ScreenHit() override = default;

    // operators
    ScreenHit& operator=(const ScreenHit&) = default;
    G4bool operator==(const ScreenHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void SetPos (G4ThreeVector xyz){ fPos = xyz; };

    G4ThreeVector GetPos() const { return fPos; };
    // methods from base class
    void Draw() override;
private:
  
    G4ThreeVector fPos;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using ScreenHitsCollection = G4THitsCollection<ScreenHit>;

extern G4ThreadLocal G4Allocator<ScreenHit>* ScreenHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* ScreenHit::operator new(size_t)
{
  if(!ScreenHitAllocator)
      ScreenHitAllocator = new G4Allocator<ScreenHit>;
  return (void *) ScreenHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void ScreenHit::operator delete(void *hit)
{
  ScreenHitAllocator->FreeSingle((ScreenHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif
