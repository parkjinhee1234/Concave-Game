using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Detector : MonoBehaviour
{

    private void OnCollisionEnter(Collision collision)
    {
        Debug.Log("OnCollisionEnte");
    }

    private void OnCollisionExit(Collision collision)
    {
        Debug.Log("OnCollisionEnte");
    }
}
