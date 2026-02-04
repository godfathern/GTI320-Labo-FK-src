#pragma once

#include "Math3D.h"
#include <vector>
#include <string>

namespace gti320
{

    class Link
    {
    public:
        // Constructor.
        //  @a _parent = the parent link
        //  @a _eulerAng = the initial rotation
        //  @a _trans = the position relative to the parent
        //
        Link(const std::string& _name, Link* _parent, const Vector3f& _eulerAng, const Vector3f& _trans);

        // Return true if this link is the root, false otherwise.
        //
        inline bool isRoot() const { return (parent == nullptr);  }

        // Return true if this link is an endEffector, false otherwise.
        //
        inline bool isEndEffector() const { return endEffector; }

        // Compute the forward kinematics.
        //
        void forward();

        Link* parent;                                   // Parent of this link (if the root, nullptr)
        std::vector<Link*> enfants;                     // Child links.
        std::string name;                               // Name of the link

        bool endEffector;                               
        Vector3f eulerAng;                              // Euler angles giving rotation relative to the parent.
        Vector3f trans;                                 // Translation giving position relative to the parent.
        Matrix4f M;                                     // Global rigid transformation of the link, computed in forward().

    };

    class Armature
    {
    public:
        // Constructor.
        //
        Armature();

        // Destructor.
        //
        ~Armature();

        // Forward kinematics to update the global transforms of all links.
        //
        void updateKinematics();

        // Extract the Euler angles of specific links and store them in the dense vector @a theta. 
        // The indices of links are contained in vector @a ind, in the same order.
        //
        void pack(const Vector<int, Dynamic>& ind, Vector<float, Dynamic>& theta);

        // Update the Euler angles of specific links in the armature from the vector @a theta.
        // The indices of links are contained in vector @a ind, in the same order.
        // 
        void unpack(const Vector<int, Dynamic>& ind, const Vector<float, Dynamic>& theta);

        // Change the root of the armature to @a newRoot.
        // The parent->enfant graph must be updated, as well as the 
        // relative translation and euler angles of each link affected.
        //
        void reroot(Link* newRoot);

        std::vector<Link*> links;                       // All of the articulated links that make-up the armature.
        Link* root;                                     // The root link.
    };
}

