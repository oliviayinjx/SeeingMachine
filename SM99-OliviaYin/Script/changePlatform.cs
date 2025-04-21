using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class changePlatform : MonoBehaviour
{
    public Color white;
    public Color grey;

    SpriteRenderer spriteRenderer;
    // Start is called before the first frame update
    void Start()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
        changeGreyColor();
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    public void changeWhiteColor()
    {
        spriteRenderer.color = white;
        gameObject.GetComponent<BoxCollider2D>().isTrigger = false;
        spriteRenderer.enabled = true;
    }

    public void changeGreyColor()
    {
        //spriteRenderer.color = grey;
        spriteRenderer.enabled = false;

        gameObject.GetComponent<BoxCollider2D>().isTrigger = true;
    }
}
