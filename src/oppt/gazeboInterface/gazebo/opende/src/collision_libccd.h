#pragma once

int dCollideCylinderCylinder(dxGeom *o1, dxGeom *o2, int flags,
			                 dContactGeom *contact, int skip);

int dCollideBoxCylinderCCD(dxGeom *o1, dxGeom *o2, int flags,
			               dContactGeom *contact, int skip);

int dCollideCapsuleCylinder(dxGeom *o1, dxGeom *o2, int flags,
			                dContactGeom *contact, int skip);

int dCollideConvexBoxCCD(dxGeom *o1, dxGeom *o2, int flags,
                         dContactGeom *contact, int skip);

int dCollideConvexCapsuleCCD(dxGeom *o1, dxGeom *o2, int flags,
                             dContactGeom *contact, int skip);

int dCollideConvexCylinderCCD(dxGeom *o1, dxGeom *o2, int flags,
                              dContactGeom *contact, int skip);

int dCollideConvexSphereCCD(dxGeom *o1, dxGeom *o2, int flags,
                            dContactGeom *contact, int skip);

int dCollideConvexConvexCCD(dxGeom *o1, dxGeom *o2, int flags,
                            dContactGeom *contact, int skip);

