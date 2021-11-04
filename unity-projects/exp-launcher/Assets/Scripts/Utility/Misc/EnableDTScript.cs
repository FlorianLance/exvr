

// unity
using UnityEngine;

[ExecuteInEditMode]
public class EnableDTScript : MonoBehaviour {

    [SerializeField]
    float eulerAngX;
    [SerializeField]
    float eulerAngY;
    [SerializeField]
    float eulerAngZ;

    void Update() {

        eulerAngX = transform.localEulerAngles.x;
        eulerAngY = transform.localEulerAngles.y;
        eulerAngZ = transform.localEulerAngles.z;

    }
}
